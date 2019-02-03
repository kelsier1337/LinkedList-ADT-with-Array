/* 
* CPSC 2150, Assignment #3
* Student Last Name:
* Student First Name:
* Student Number:
* 
*/
#include "LList.h"

int main() {
   LList list;
   list.cons(15);
   list.cons(3);
   list.cons(16);
   // list.cons(4);
   // list.cons(33);
   // list.cons(32);
   #ifndef NDEBUG
   list.dumpNodesArray();
   #endif
   return 0;
}
