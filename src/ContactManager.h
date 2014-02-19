#ifndef CONTACT_MANAGER_H_
#define CONTACT_MANAGER_H_
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.h"
#include "Contact.h"
#include "Treap.h"  // for Task 2
#include "Trie.h"

class ContactManager {
private:
	LinkedList<Contact> contacts;
public:
    Treap<string, Contact*> tree;  // for Task 2
    Trie trie;
public:
	ContactManager();
	bool loadFromFile(string fileName);
	void add(string name, string phone_number);
	void displayNumber(string phone_number);
	void displayContacts(string smartNumber);
	friend ostream& operator<<(ostream& o, ContactManager & c);
};
//=================================================================
ContactManager::ContactManager() {
	srand(time(NULL));
	contacts.delimiter = "\n";
}
//=================================================================
bool ContactManager::loadFromFile(string fileName) {

	fstream myFile;
	string phone_number, name;
	int fileSize;
	char *buffer;

	myFile.open(fileName.c_str(), ios::in | ios::binary);

	if (myFile.fail())
		return false;

	myFile.seekg(0, ios::end);
	fileSize = myFile.tellg();

	if (myFile.fail())
		return false;

	buffer = new char[fileSize];
	myFile.seekg(0, ios::beg);

	if (myFile.fail()) {
		delete[] buffer;
		return false;
	}

	myFile.read(buffer, fileSize);	//Read all at once

	if (myFile.fail()) {
		delete[] buffer;
		return false;
	}

	myFile.close();

	for (int i = 0; i < fileSize; ++i) {
		if (buffer[i] == ' ') {
			int j;
			for (j = i + 1; j < fileSize && buffer[j] != '\n'; ++j)
				name += buffer[j];
			add(name, phone_number);
			i = j;
			name = "";
			phone_number = "";
		}
		else
			phone_number += buffer[i];
	}

	delete[] buffer;
	return true;
}
//=================================================================
void ContactManager::add(string name, string phone_number) {
	Contact temp(name);
	Contact *n = &(contacts.addSorted(temp)->value);
	n->addPhoneNumber(phone_number);
	tree.insert(phone_number, n);
	trie.addContactPointer(n);
}
//=================================================================
void ContactManager::displayContacts(string smartNumber) {
	cout << "Contacts that match " << smartNumber << ":" << endl;
	cout << trie.find(smartNumber) << endl;
}
//=================================================================
void ContactManager::displayNumber(string phone_number) {
	Contact *n = tree.find(phone_number);
	if (n == NULL)
		cout << phone_number;
	else
		cout << n->getName();
	cout << endl;
}
//=================================================================
ostream& operator<<(ostream& o, ContactManager & c) {
	o << c.contacts;
	return o;
}

#endif  /* CONTACT_MANAGER_H_ */
