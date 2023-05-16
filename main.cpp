 //William Wong
 //4/28/23
 //This is a Red Black Tree project, which creates a balanced search tree. 

 //William Wong
 //5/18/23
 //This new iteration toward the Red Black Tree allows the user to search for a number and also removes nodes
 //in which the tree will be able to update

 #include "Node.h"
 #include <cstring>
 #include <iostream>
 #include <fstream>
 using namespace std;

 //Sources used for Red Black Tree:
 //https://www.programiz.com/dsa/red-black-tree#:~:text=In%20left%2Drotation%2C%20the%20arrangement,arrangements%20on%20the%20left%20node.&text=If%20y%20has%20a%20left,the%20left%20subtree%20of%20y%20.&text=If%20the%20parent%20of%20x,the%20left%20child%20of%20p%20./


 //Function prototypes below

 Node* insert(Node* &, Node*);
 void add(Node*, Node*);
 void rearrange(Node*, Node* &);
 void print(Node*, int);
 void leftRotate(Node* &, Node*);
 void rightRotate(Node* &, Node*);
 void uncleFunc(Node*, Node* &);
 int pow(int, int);
 void charToIntArray(char*, int* &, int &);

 //Additional function prototypes below

 void remove(Node* &, Node* &);
 void doubleBlack(Node* &, Node*);
 Node* getNode(Node*, int);
 Node* leftestNode(Node*);
 bool search(Node*, int);

 int main() {

   bool cont = true;
   char* name = new char[50];
   char* userIn = new char[1000];
   Node* root = NULL;
   int value = 0;

   while(cont == true) {

     cout << "Please choose one of these actions --> ADD, READ, REMOVE, SEARCH, PRINT, or QUIT:" <<endl;
     cin >> name;
     cin.ignore();
     if (strcmp(name, "ADD") == 0) { //if user input is that of ADD

       cout << "Please enter the number that you want added: ";
       cin >> value;
       root = insert(root, new Node(value)); //Helps to add toward the tree
       
       cout << endl;
       
     }
     else if (strcmp(name, "READ") == 0) {

       while(cont == true) { //reptition of asking for file

	 cout << "Please enter the name of your file: " << endl;
	 cin.getline(name, 50, '\n');
	 ifstream fileStream (name);
	 if (fileStream.is_open()) { //helps to open the file through user inputted name

	   fileStream.getline(userIn, 150);
	   cont = false;
	   
	 }
	 else {
	   cout << "Invalid!" << endl;
	 }
	 fileStream.close();
       }

       cont = true; //reset
       int*numInput = new int[101];
       int size = 0;
       charToIntArray(userIn, numInput, size); //conversion from char to int aray

       for(int i = 0; i < (size); i++) { //helps to insert num within tree
	 root = insert(root, new Node(numInput[i]));
       }
     
   }
     else if (strcmp(name, "REMOVE") == 0) { //Deletion part of RBT
       cout << "Please enter which number you want to be removed: ";
       cin >> value;

       if(search(root, value) == true) { //looks if num is inside tree
	 Node* temp = getNode(root, value); //traversed toward node
	 cout << temp->getValue() << endl;
	 remove(root, temp); //removes node
       }
       else {
	 cout << "Invalid number!";
       }
       cout << endl;
      
     }
     else if (strcmp(name, "PRINT") == 0) { //helps to print the picture of the tree!

     print(root, 0);
     
   }
     else if (strcmp(name, "SEARCH") == 0) { //helps user to search for inputted number

       cout << "Please enter the number in which you want to search: ";
       cin >> value;

       if (search(root, value) == true) { //traverses tree to find node value which was inputted
	 cout << "This number: " << value << " is existing within the tree.";
       }
       else {
	 cout << "This number: " << value << " is not existing within the tree.";
       }
       cout << endl;
       
     }
     
     else if (strcmp(name, "QUIT") == 0) { //stop program 

     cout << "Adios amigo!" << endl;
     cont = false;
     return 0;
     
   }
   else {

     cout << "Invalid! Try again" << endl;
     
   }
  
  } 
   cout << endl;
   return 0;

 }
   
void leftRotate(Node* &root, Node* blue) { //node blue

  if (blue->getRight() == NULL) { //yellow cease to occur
     return;
   }

  Node* yellow = blue->getRight(); //yellow pointer
  Node* parent = blue->getParent(); //blue parent
  blue->setRight(yellow->getLeft()); //blue right = red
  yellow->setLeft(blue); //yellows left is blue
  blue->setParent(yellow); //yellow blues parent

  if(blue->getRight() != NULL) { //exists red
     
    blue->getRight()->setParent(blue); //setting blue as the reds parent
		    
   }
  
  if(parent != NULL) { //blue not root

    if(blue == parent->getLeft()) { //blue left child of parent
	
      parent->setLeft(yellow);
      
     }
    else if (blue == parent->getRight()) { //blue right child of parent

      parent->setRight(yellow);
			  
     }
		    
    }
      
    yellow->setParent(parent);
		  
 }

 void rightRotate(Node* &root, Node* yellow){

   if (yellow->getLeft() == NULL){
    return;
   }
  
   Node* blue = yellow->getLeft(); //blue left child of yellow
   Node* parent = yellow->getParent(); //the parent of yellow
   yellow->setLeft(blue->getRight());
   blue->setRight(yellow); 
   yellow->setParent(blue); 

   if (yellow->getLeft() != NULL){ //checking red is existing
     
     yellow->getLeft()->setParent(yellow);
     
   }
   if (parent != NULL){ //if yellow is not root
     if (yellow == parent->getLeft()){
       
       parent->setLeft(blue);
       
     }
     else if (yellow == parent->getRight()){ //if yellow is right child of parent

       parent->setRight(blue);

     }
   }
   blue->setParent(parent); //previous parent of yellow not blues parent
 }

void add(Node* current, Node* node){ //helps to add new node 

   if (current == NULL){
     current = node;
     return; 
   }
   if (node->getValue() < current->getValue()){ //if the value is smaller put to left
     if (current->getLeft() != NULL){ //if not leaf, go toward left
       
       add(current->getLeft(), node);
       return;
       
     }
     else{ //node left child of current
       current->setLeft(node);
     }
   }
   else{ //value larger/equal
     if (current->getRight() != NULL){
       
       add(current->getRight(), node);
       return;
       
     }
     else{//node right child of current
       
       current->setRight(node);
       
     }
     
   }
   //below sets current as parent of the new node
   node->setParent(current);
 }

 Node* insert(Node* &root, Node* node){ //helps to add and reoganize the tree
   
   add(root, node);
   rearrange(node, root);
   root = node; 
   while(root->getParent() != NULL){
     
     root = root->getParent(); //helps to continuously retriving parent until parent is the null for root
     
   }
   return root;
 }

void print(Node* current, int depth){ //visualization of tree

   if (current == NULL){

     return;

   }
   print(current->getRight(), depth+1); 
   for(int i = 0; i < depth; i++){

     cout << "\t"; //tabbing for visualization

   }
   if (current->getColor() == 1){ //colore is printed beforehand

     cout << "B ";

   }
   if (current->getColor() == 2){

     cout << "R ";

   }
   
   cout << current->getValue() << endl;
   print(current->getLeft(), depth+1); 

 }

 void rearrange(Node* current, Node* &root){ 

   if (current->getParent() == NULL){ //when current is root
     current->setColor(1); //color is black
   }
   else if (current->getParent()->getColor() == 1){ //current parent black
   
   }
   else if (current->getUncle() != NULL && current->getUncle()->getColor() == 2){ //uncle is red

     current->getParent()->setColor(1); //parent/uncle set to black
     current->getUncle()->setColor(1);
     current->getGrandparent()->setColor(2); //the grandparent becomes red
     rearrange(current->getGrandparent(), root);

   }
   else{ //two cases here 
     uncleFunc(current, root);
   }
 }

 void uncleFunc(Node* current, Node* &root){ //if uncle black

   Node* parent = current->getParent();
   Node* grandparent = current->getGrandparent();

   if (current == parent->getRight() && parent == grandparent->getLeft()){

     leftRotate(root, parent); //rotating the parent to other direction of grandparent
     current = current->getLeft(); //previous parent turns to current

   }
   else if (current == parent->getLeft() && parent == grandparent->getRight()){

     rightRotate(root, parent);
     current = current->getRight();

   }
  
   parent = current->getParent();
   grandparent = current->getGrandparent();

   if (current == parent->getLeft()){ //grandp, parent, current creating line on left
     rightRotate(root, grandparent); //rotating the grandparent
   }
   
   else{ //the line is on the right
     leftRotate(root, grandparent);
   }
   
   if (root == grandparent){ 
     root = parent;
   }
   parent->setColor(1); //fixing colors for the parent and grandparent
   grandparent->setColor(2);
 }
 
 void charToIntArray(char* carray, int* &iarray, int &size){ //conversion of char array to int array

   int counter = 0;
   int place = 0;
   for (int i = 0; i < strlen(carray); i++){ //goes within the elments of the char array
     if (carray[i] >= '0' && carray[i] <= '9'){
       if (place != 2){ //1s / 10s location
	 counter = (counter * pow(10, place)) + (carray[i] - '0'); //added to counter
       	 place++;
       }
       else{ //100s place
	 counter = (counter * pow(10, place-1)) + (carray[i] - '0');
       }
       if (i == strlen(carray)-1){ //adding the last element to the array
        iarray[size++] = counter;
       }
     }
     else if (carray[i] == ' '){ //checking is there is space
       iarray[size++] = counter;
       counter = 0;
       place = 0;
     }
   }
 }
 
 int pow(int a, int b){ //power function here

   int x = 1;
   for (int i = 1; i <= b; i++){

     x *= a; //multiplification of a by itself

   }
   return x;
 }

 Node* getNode(Node* current, int value) { //this function helps to return node 

   if(current == NULL) {
     return current;
   }
   if (value == current->getValue()) { //if value found it stops looking
     return current;
   }
   if (value < current->getValue()) { //left child is looked for if the value is smaller
     return getNode(current->getLeft(), value);
   }
   if (value > current->getValue()) { //right child is looked for if value is larger
     return getNode(current->getRight(), value);
   }
 }

 Node* leftestNode(Node* current) { //helps to find the left most node within tree

  if (current->getLeft() == NULL) { //if last node, return node
     return current;
   }
   else {
     return leftestNode(current->getLeft()); //traversal toward left child
   }
   
 }

 bool search(Node* current, int value) { //helps to search for node user inputted              

   while (current != NULL) {
     if (value == current->getValue()) { //if value within tree, true                            
       return true;
     }
     if (value < current->getValue()) { //traversal                                              
       return search(current->getLeft(), value);
     }
     if (value > current->getValue()) {
       return search(current->getRight(), value);
     }
   }
   return false; //if value not find, false                                                      
 }

 Node* replace(Node* node) { //helps to look for the replacement node

   if (node->getLeft() != NULL && node->getRight() != NULL) { //goes toward the leftest of left!
     return leftestNode(node->getRight());
   }
   if (node->getLeft() == NULL && node->getRight() == NULL) { //if there are no children
     return NULL;
   }
   if (node->getLeft() != NULL) { //if there is a left child go left
     return node->getLeft();
   }
   else { //go right
     return node->getRight();
   }
 }

 void remove(Node* &root, Node* &current) { //helps to remove node 

   Node* temp = replace(current);
   Node* parent = current->getParent();

   if(temp == NULL) { //if the current is leaft
     if (current == root) { //nodes root
       root = NULL;
     }
     else {
       if ((temp == NULL || temp->getColor() == 1) && (current->getColor() == 1)) { //if both black and the replacement is leaf
	 doubleBlack(root, current);
       }
       else {
	 if (current->getSibling() != NULL) {
	   current->getSibling()->setColor(2); //sibling red
	 }
       }
       if (parent->getRight() == current) { //reassigning
	 parent->setRight(NULL);
       }
       else {
	 parent->setLeft(NULL);
       }
     }
     delete current;
     return;
   }
   if (current->getLeft() == NULL || current->getRight() == NULL) { //if only one child
     if (current == root) { //coying value then deleting if root
       current->setValue(temp->getValue());
       current->setLeft(NULL);
       current->setRight(NULL);
       delete temp;
     }
     else { //helping to move the temporary value up tree
       if (parent->getLeft() == current) {
	 parent->setLeft(temp);
       }
       else {
	 parent->setRight(temp);
       }
       delete current;
       temp->setParent(parent);
       if ((temp == NULL || temp->getColor() == 1) && (current->getColor() == 1)) { //both black
	 doubleBlack(root, temp);
       }
       else {
	 temp->setColor(1);
       }
     }
     return;
   }
   int temp2 = temp->getValue(); //if the temporary has two values helps to swap them
   temp->setValue(current->getValue());
   current->setValue(temp2);
   remove(root, temp);
   
 }

 void doubleBlack(Node* &root, Node* node) { //helps to sort with double black node

   if (node == root) {
     return;
   }

   Node* parent = node->getParent();
   Node* sibling = node->getSibling();
   if (sibling == NULL) { //if there is no sibling
     doubleBlack(root, parent);
   }
   else {
     if (sibling->getColor() == 2) { //if the sibling is red
       parent->setColor(2);
       sibling->setColor(1);
       if (parent->getLeft() == sibling) { //if the sibling is on the left
	 rightRotate(root, parent);
       }
       else { // if the sibling is on the right
	 leftRotate(root, parent);
       }
       doubleBlack(root, node);
     }
     else { //if the sibling is black
       if ((sibling->getLeft() != NULL && sibling->getLeft()->getColor() == 2) || (sibling->getRight() != NULL && sibling->getRight()->getColor() == 2)) {
	 if ((sibling->getLeft() != NULL) && (sibling->getLeft()->getColor() == 2)) {
	   if (parent->getLeft() == sibling) {
	     sibling->getLeft()->setColor(sibling->getColor());
	     sibling->setColor(parent->getColor());
	     rightRotate(root, parent);
	   }
	   else { //if the sibling is on the right
	     sibling->getLeft()->setColor(parent->getColor());
	     rightRotate(root, sibling);
	     leftRotate(root, parent);
	   }
	 }
	 else { // if the rihgt child is red
	   if(parent->getLeft() == sibling) {
	     sibling->getRight()->setColor(parent->getColor());
	     leftRotate(root, sibling);
	     rightRotate(root, parent);
	   }
	   else { //if the sibling is on the rihgt
	     sibling->getRight()->setColor(sibling->getColor());
	     sibling->setColor(parent->getColor());
	     leftRotate(root, parent);
	   }
	 }
	 parent->setColor(1);
       }
       else { //both are black
	 sibling->setColor(2);
	 if (parent->getColor() == 1) {
	   doubleBlack(root, parent);
	 }
	 else {
	   parent->setColor(1);
	 }
       }
     }
   }
 }
			
