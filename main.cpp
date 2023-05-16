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
 void leftRotate(Node*);
 void rightRotate(Node*);
 void uncleFunc(Node*, Node* &);
 int pow(int, int);
 void charToIntArray(char* carray, int* &iarray, int &size);


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
     else if (strcmp(name, "REMOVE") == 0) {
       cout << "Please enter which number you want to be removed: ";
       cin >> value;

       //insert search/remove functions

       
       
     }
     else if (strcmp(name, "PRINT") == 0) { //helps to print the picture of the tree!

     print(root, 0);
     
   }
     else if (strcmp(name, "PRINT") == 0) {

       cout << "Please enter the number in which you want to search: ";
       cin >> value;

       //search function here
       
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
   
void leftRotate(Node* blue) { //node blue

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

 void rightRotate(Node* yellow){

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

     leftRotate(parent); //rotating the parent to other direction of grandparent
     current = current->getLeft(); //previous parent turns to current

   }
   else if (current == parent->getLeft() && parent == grandparent->getRight()){

     rightRotate(parent);
     current = current->getRight();

   }
  
   parent = current->getParent();
   grandparent = current->getGrandparent();

   if (current == parent->getLeft()){ //grandp, parent, current creating line on left
     rightRotate(grandparent); //rotating the grandparent
   }
   
   else{ //the line is on the right
     leftRotate(grandparent);
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
