#ifndef LLIST_H
#define LLIST_H
/* 
* CPSC 2150, Assignment #3 (expand code defined by Gladys Monagan)
* Student Last Name:
* Student First Name:
* Student Number:
* Program ...
* 
*/
#include <string>
class  LList {
   public:
      // create an empty list
      LList();
      // determine if the list is empty
      bool empty() const;
      // give the length of the list
      int length() const;
      // return the first element of the list and UNDEFINED if the list is empty
      short first() const;
      // return the last element of the list and UNDEFINED if the list is empty
      short last() const;
      // insert x at the beginning of the linked list
      // postcondition: x is the first element
      // we assuming that there is enough heap memory
      void cons(short x);
      // append x to the end of the linked list
      // postcondition: x is the last element
      // we assuming that there is enough heap memory
      void append(short x);
      // delete the first occurrence of x in the list 
      // postcondition: return true if x was removed, false otherwise
      bool remove(short x); 
      // transfer all the elements from the 'other' list into this list
      //    -> pos indicates the position (starting with the 0th position) where
      //       the elements from 'other' will be transferred into this list
      //    -> e.g. when pos == 0, all the elements of the 'other' list will
      //       be placed before the (original) elements of this list.
      // precondition: pos >= 0 
      // postcondition: all the elements of the 'other' list are removed 
      // from the 'other' list and placed into this list at position 0
      // The lengths of both lists change: the length of the 'other' list becomes
      // zero (as it no longer has any elements)
      // If pos >= length(), then all the elements of the 'other' list are 
      // appended to this list
      void splice(LList& other, int pos);
      // search x in the list
      // postcondition: return true if found, false otherwise
      bool search(short x) const;
      // mutator method (function) that reverses the list
      void reverse();
      // returns a string consisting of all the elements of the list
      // in the order in which they are in the list from first to last in this format:
      //    -> the string starts with "[" followed by a DELIMETER
      //    -> for each element: the element's value followed by a DELIMETER
      //    -> the string finishes with "]"
      // e.g. a string of 3 elements  "[ 41 36 999 ]"
      std::string toString() const;
      // copy constructor
      // we assuming that there is enough heap memory
      LList(const LList &other);      
      //WHAT IS THE COPYLIST FUNCTION FROM THE CODE THAT WE SAW IN THE LAB??
      //STANDARD FUNCTION>?? NO? WHERE IS IT?
      // overloaded assignment operator
      // we assuming that there is enough heap memory
      LList operator = (const LList &other);
      // destructor
      ~LList();
      // initialize to std::string(" ");
      static const std::string DELIMETER;
      // value returned when there is no last or no first in the empty list
      static const short UNDEFINED;
      
      #ifndef NDEBUG
      // dump the array, print the contents with std::cout
      void dumpNodesArray() const;
      #endif

   private:
      struct Node {
         short item;
         int next;
      };

      // the array of nodes has INITIAL_CAPACITY nodes
      static const int INITIAL_CAPACITY = 4;

      // dynamic array of nodes
      Node *nodes;

      // index of the first node in the linked list
      int head;

      // index of the first node of the "free nodes' list"
      int free;

      // size of the current array.
      int size;

      // index of the end of the free list
      int freeEnd;
      
};
#endif
