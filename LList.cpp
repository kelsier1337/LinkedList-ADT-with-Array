/* 
* CPSC 2150, Assignment #3
* Student Last Name:
* Student First Name:
* Student Number:
* Program ...
* 
*/
#include "LList.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <climits>  // SHRT_MIN //why is this here??
#include "LList.h"

const std::string LList::DELIMETER = std::string(" "); //delimiter to use for the dumping/printing of the array.
const short LList::UNDEFINED = -1; 
const int INITIAL_CAPACITY = 4;
int capacity = INITIAL_CAPACITY;
using std::cout;

LList::LList() {
	head = UNDEFINED;
	free = 0;
	nodes = new Node[capacity];
	for(int i = 0; i < capacity; i++) {
		nodes[i].next = i + 1;
		nodes[i].item = SHRT_MAX;
	}
	nodes[capacity - 1].next = UNDEFINED;
	size = 0;
}
//check if the list is empty
//return true if empty and false otherwise.
bool LList::empty() const {
	return (head == UNDEFINED);
}
//return the length of the linked list
int LList::length() const {
	int count = 0;
	int i = head;
	while(nodes[i].next != UNDEFINED) {
		count++;
		i = nodes[i].next;
	}
	return count;
}
//return the first node in the linked list
short LList::first() const {
	//if the list is empty, return the undefined value
	if(empty()) {
		return UNDEFINED;
	}
	//else return the item at the beginning (head) node.
	else {
		return nodes[head].item;
	}
}
//return the last element in the linked list.
short LList::last() const {
	//don't want to change head so put it's value in i and use that for traversal
	int i = head;
	//if the list is empty, return undefined
	if(empty()) {
		return UNDEFINED;
	}
	//else, go to the end node, which will have the undefined index as it's next index
	//to signify the end of the list.
	else {
		while(nodes[i].next != UNDEFINED) {
			i = nodes[i].next;
		}
		//then return the item in that node
		return nodes[i].item;
	}
}

//constructs a new node at the beginning of the list. 
//x is the first element after execution of this function.
void LList::cons(short x) {
	//special case for when the linked list is full.
	if(size == capacity) {
		//create a new array of nodes
		Node* newNodes;
		newNodes = new Node[capacity * 2];
		//copy everything from the previous array to the new array.
		for(int i = 0; i < capacity; i++) {
			newNodes[i] = nodes[i];
		}
		//the free in the new array should start from the previous' capacity + 1
		free = capacity;
		//the new capacity of the new array.
		capacity = capacity * 2;
		//the free nodes should be updated according to the new capacity
		for(int i = free; i < capacity - 1; i++) {
			newNodes[i].next = i + 1;
		}
		
		//delete the memory at the old address
		//delete nodes;
		//get the memory of the  new address to the old adress.
		nodes = newNodes;
		//set the last free node to undefined
		nodes[capacity - 1].next = UNDEFINED;	
	}
	//Special case for the first element in the list
	if(empty()) {
		//the new head takes the first free index
		head = free;
		//the free index goes to the next free index
		free = nodes[free].next;
		//item in the argument is added to the item in the node at head
		nodes[head].item = x;
		//only one element and it's next needs to be null/undefined 
		//to signify the end of the "used linked list"
		nodes[head].next = UNDEFINED;
	}
	else {
		//same process as for the special case above, except that the next index of
		//this head needs to point to the previous head.
		//I'M NOT CHANGING THE FIRST HEAD'S NEXT VALUE. IT'S STILL UNDEFINED
		//EVERYTIME THE CONS IS CALLED.
		//TODO -- DONE, IT'S ALL GOOD
		int temp = head;
		head = free;
		free = nodes[free].next;
		nodes[head].item = x;
		nodes[head].next = temp;
		//increase the size of the linked list
		size++;
	}	

	// previous attempt. wrong attempt.
	// int temp = free;
	// free = nodes[free].next;
	// int tempHead = head;
	// head = temp;
	// nodes[head].item = x;
	// nodes[head].next = tempHead;
	// size++;
}

//append a new node a the end of the linked list. 
//postcondition: x is the last element in the linked list.
void LList::append(short x) {
	//check if the array is full, make new array of double size if it is full.
	//this is the same process as in the cons function.
	if(size == capacity) {
		Node* newNodes;
		newNodes = new Node[capacity * 2];
		for(int i = 0; i < capacity; i++) {//ASK DR. MONAGAN ABOUT THE NEXT ADDRESSES OF THE FREE NODES IN THE NEW ARRAY
			newNodes[i] = nodes[i];
		}
		//the new free will start from the previous capacity + 1;
		free = capacity + 1;
		capacity = capacity * 2;
		for(int i = free; i < capacity - 1; i++) {
			nodes[i].next = i + 1;
		}
		nodes[capacity - 1].next = UNDEFINED; 
		nodes = newNodes;
		delete newNodes;
	}
	//store the value of head because I don't want to change head.
	//use i for traversal instead
	int i = head;
	while(nodes[i].next != UNDEFINED) {
		//stop at the node which has undefined for it's "next" value.
		i = nodes[i].next;
		
	}
	//Store the next free node's index in temp
	int temp = nodes[free].next;
	//change the undefined value of the end of the list to the next free 
	//node's index. 
	nodes[i].next = free;
	//change the item at that (free) value to the value we need to change it to
	nodes[free].item = x;
	//set that node's next address to undefined to signify the end of the linked list.
	nodes[free].next = UNDEFINED;
	//reset the value of the free node index from what we saved earlier in temp
	free = temp;
	//increase the size of the linked list
	size++;
}

//remove the specified element from the linked list. if the element exists in any node,
//remove the node and return true if successful(found and removed) and false if the 
//element was not found in the list
bool LList::remove(short x) {
	//check if the list is empty, return false if empty 
	//because no element to remove.
	if(empty()) {
		return false;
	}
	//special case for if the item is in the head node
	if(nodes[head].item == x) {
		//tmep to store the current free node.
		int temp = free;
		//move the next free node to the head position
		free = head;
		//move the head to the node after the deleted node
		head = nodes[head].next;
		//update the next node in line for the free nodes with the previous node.
		nodes[free].next = temp;
	}
	//else, traverse the list until you find the node with 
	//the element passed as the argument.
	//use i for traversal
	int i = head;
	//keep track of the node at the prev index.
	int prev = head;
	//keep going until the item is not equal to x or 
	//undefined; as it signifies the end of the list
	while(nodes[i].next != UNDEFINED) {
		//if the value is not equal to the value we need, move onto
		// the next node
		if(nodes[i].item != x) {
			prev = i;
			i = nodes[i].next;
		}
		//else, delete the node and update the free nodes
		else {
			//store the current free node
			int temp = free;
			//store the next node of the node to be deleted
			int nextNode = nodes[i].next;
			//set the free node to the node with the value to be removed
			free = i;
			//set the next of the free node to the previous free node
			nodes[free].next = temp;
			//set the previous node of the deleted node to the one 
			//after the deleted node
			nodes[prev].next = nextNode;
			//break the while loop
			break;
			//return true as x was found and deleted
		}

	}
	return true;
}

//search for the argument in the linked list.
bool LList::search(short x) const {
	//return false if the list is empty
	bool flag = false;
	if(empty()) {
		return flag;
	}
	//else traverse the list until you find the item or you reach the end 
	//of the linked list
	//don't want to change the head, so use i to traverse
	int i = head;
	while(nodes[i].next != UNDEFINED) {
		//keep traversing if the item is not found
		if(nodes[i].item != x) {
			i = nodes[i].next;
		}
		//set flag to true if the item is found
		else {
			flag = true;
		}
	}
	return flag;
}


//reverse the list
void LList::reverse() {






	//this implementation is wrong, think again.
	//return if the list is empty
	// if(empty()) {
	// 	return;
	// }
	// int len = length();
 //    for(int i = 0; i < (len / 2); i++) {
 //        Node temp = nodes[i]; 
 //        nodes[i] = nodes[(len - 1) - i];   
 //        nodes[(len - 1) - i] = temp;
 //    }
}

//copy constructor
LList::LList(const LList &other) {
	//check if the other list is empty
	if(other.head == UNDEFINED) {
		//if the other list is empty, set the head of this 
		//list to UNDEFINED because this should alos be empty
		head = UNDEFINED;
	}
	//else, copy the first node, i.e. the head of the other list
	else {
		head = other.head;
		//copy all the other nodes

	}

}

LList LList::operator = (const LList &other) {

}

LList::~LList() {
	delete[] nodes;
}






#ifndef NDEBUG 
#include <iostream>
#include <iomanip>
using std::cout;
using std::setw;
using std::endl;
      
void LList::dumpNodesArray() const { 
   // cout << "free = " << free << "\t";
   // cout << "head = " << head << "\t";

	for(int i = 0; i < capacity; i++) {
		cout << nodes[i].item << " -> ";
	}

	cout << endl;
	
	int i = head;
	cout << "head(" << head << ") = ";
	bool head_flag = true;
	while(head_flag) {
		cout << nodes[i].item << "|" << nodes[i].next <<  " -> ";
		if(nodes[i].next == UNDEFINED)
			head_flag = false;
		i = nodes[i].next;
	}
	cout << endl;
	cout << "free(" << free << ") = ";

	int j = free;
	bool free_flag = true;
	while(free_flag) {
		cout << nodes[j].item << "|" << nodes[j].next << "->"; 
		if(nodes[j].next == UNDEFINED)
			free_flag = false;
		j = nodes[j].next;
	}
	cout << endl;

   // etc ....
}

#endif
