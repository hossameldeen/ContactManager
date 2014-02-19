//============================================================================
// Name        : CS214-Project.cpp
// Author      : Hossam El-Deen, Waleed, Bassem
//============================================================================

#include <iostream>
#include "ContactManager.h"
using namespace std;

int main() {
	//For testing and a simple demo
	ContactManager CM;
	CM.loadFromFile("all-contacts.in");
	CM.displayNumber("01060626992");
	cout << endl;
	CM.displayContacts("65");
	return 0;
}
