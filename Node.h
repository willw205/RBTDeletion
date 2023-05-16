 #ifndef NODE_H
 #define NODE_H

 #include <iostream>
 using namespace std;

 //Grandparents, sibling, and uncle are impelmented within class
 
 class Node {
  public:
   Node(int newvalue);
   int getColor();
   int getValue();
   Node* getLeft();
   Node* getRight();
   Node* getParent();
   Node* getGrandparent();
   Node* getUncle();
   Node* getSibling();
   void setValue(int newvalue);
   void setColor(int newcolor);
   void setLeft(Node* newleft);
   void setRight(Node* newright);
   void setParent(Node* newparent);
   ~Node();
  private:
   int value;
   int color;
   Node* left;
   Node* right;
   Node* parent;
 };


#endif
