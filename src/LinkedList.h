#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <string>
using namespace std;

template<class T>
class LinkedList {
public:
	class Node {
	public:
		T value;
		Node* next;

		Node(T v);
	};
private:
	Node* head;
public:
	string delimiter; // optional: just for printing

	LinkedList();
	Node* addSorted(T v);
	Node* get(T v);
	void operator+=(const LinkedList<T>& LL);	//For merging

	// operator overloading for printing
	template<class TT>
	friend ostream& operator<<(ostream& o, const LinkedList<TT> & c);
};
//============================================================================//
//--- Node Class Methods -----------------------------------------------------//
//----------------------------------------------------------------------------//
template<class T>
LinkedList<T>::Node::Node(T v) {
	value = v;
	next = NULL;
}
//============================================================================//
//--- Linked List Class Methods ----------------------------------------------//
//----------------------------------------------------------------------------//
template<class T>
LinkedList<T>::LinkedList() : head(NULL) {
}
//============================================================================//
template<class T>
typename LinkedList<T>::Node* LinkedList<T>::addSorted(T v) {
	Node* ptr = head;
	Node* nPtr = new Node(v);

	// if there's no nodes
	if (ptr == NULL) {
		head = nPtr; // let head point to the new node
		return head; // return that node (head)
	}

	// if there's node or more
	// check head value, if > current value
	// then add to head
	if (v < ptr->value) {
		nPtr->next = head; // let new node next point to current head
		head = nPtr;         // then let head point to the new node
		return nPtr;         // then return that node (head)
	}
	else if (v == ptr->value)
		return ptr; // if this value exists

	// check the next value of every node
	// if you reach value > current value
	// put our new node in between
	while (ptr->next != NULL) {
		if (v < ptr->next->value) {
			nPtr->next = ptr->next;
			ptr->next = nPtr;
			return nPtr;
		}
		else if (v == ptr->next->value)
			return ptr->next; // if this value exists
		ptr = ptr->next;
	}

	// if reached last node
	// let new node point to NULL
	// let last node point to new node
	nPtr->next = ptr->next;
	ptr->next = nPtr;
	return nPtr;
}
//============================================================================//
template<class T>
typename LinkedList<T>::Node* LinkedList<T>::get(T v) {
	typename LinkedList<T>::Node* ptr = head;
	// keep searching in values till you reach the value identical to v or
	// reach end of list
	while (ptr != NULL) {
		if (ptr->value == v)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}
//============================================================================//
template<class T>
void LinkedList<T>::operator+=(const LinkedList<T>& LL) {
	Node* temp = LL.head;
	while(temp != NULL) {
		this->addSorted(temp->value);
		temp = temp->next;
	}
}
//============================================================================//
template<class TT>
ostream& operator<<(ostream& o, const LinkedList<TT> & c) {
	typename LinkedList<TT>::Node* ptr = c.head;
	while (ptr != NULL) {
		if (ptr != c.head)
			o << c.delimiter; // put delimiter before nodes' values which are after head before adding to stream
		o << ptr->value;
		ptr = ptr->next;
	}
	return o;
}
#endif  /* LINKED_LIST_H_ */
