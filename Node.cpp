 #include <iostream>
 #include "Node.h"
 using namespace std;

 //below is the pass through value

 Node :: Node(int newvalue){
   value = newvalue;
   color = 2;
   left = NULL;
   right = NULL;
   parent = NULL;
 }

 int Node :: getColor(){
   return color;
 }

 int Node :: getValue(){
   return value;
 }

 Node* Node :: getLeft(){
   return left;
 }

 Node* Node :: getRight(){
   return right;
 }

 Node* Node :: getParent(){
   return parent;
 }

 Node* Node :: getGrandparent(){
   return parent->getParent();
 }

 //below gets other child

 Node* Node :: getSibling(){
   if (parent == NULL){
     return NULL;
   }
   if (this == parent->getRight()){
     return parent->getLeft();
   }
   else if (this == parent->getLeft()){
     return parent->getRight();
   }
 }

 //below is parents sibling

 Node* Node :: getUncle(){
   if (parent == NULL){
     return NULL;
   }
   else{
     return parent->getSibling();
   }
 }

 void Node:: setColor(int newcolor){
   color = newcolor;
  }

 void Node :: setValue(int newvalue){
   value = newvalue;
 }

  void Node :: setLeft(Node* newleft){
   left = newleft;
 }

 void Node :: setRight(Node* newright){
   right = newright;
 }

 void Node :: setParent(Node* newparent){
   parent = newparent;
 }

 Node :: ~Node(){
   
 }
