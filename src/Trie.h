#ifndef TRIE_H_
#define TRIE_H_

#include "LinkedList.h"
#include "Contact.h"
#include <stack>

using namespace std;

class ContactPointer {
private:
	Contact* contact;
public:
	ContactPointer() {
		contact = NULL;
	}
	ContactPointer(Contact* n) {
		contact = n;
	}
	bool operator<(const ContactPointer& n) {
		return contact->getName() < n.contact->getName();
	}
	bool operator==(const ContactPointer& n) {
		return contact->getName() == n.contact->getName();
	}
	string getName() {
		return contact->getName();
	}
	friend ostream& operator<<(ostream& o, const ContactPointer& contactPointer) {
		o << *(contactPointer.contact);
		return o;
	}
};

class Trie{
public:
	class Node {
	private:
		Node* arc[10];
		LinkedList<ContactPointer> contacts;
	public:
		Node();
		void addContactPointer(ContactPointer);
		friend class Trie;
	};
private:
	Node* root;
public:
	Trie();
	void addContactPointer(ContactPointer);
	LinkedList<ContactPointer> find(string smartName);
};
//============================================================================//
Trie::Node::Node() {
	for (int i = 0; i < 10; ++i)
		arc[i] = NULL;
	contacts.delimiter = "\n";
}
//============================================================================//
void Trie::Node::addContactPointer(ContactPointer contact) {
	contacts.addSorted(contact);
}
//============================================================================//
Trie::Trie() {
	root = new Node;
}
//============================================================================//
void Trie::addContactPointer(ContactPointer contact) {
	//Converting to smartName .. example: Bob -> 262
	string smartName;
	for (unsigned int i = 0; i < contact.getName().size(); ++i) {
	    if (contact.getName()[i] == ' ')
	    	smartName += '0';
		else if (tolower(contact.getName()[i]) < 's')
			smartName += (char) ((tolower(contact.getName()[i]) - 'a') / 3 + '2');
		else if (tolower(contact.getName()[i]) < 'z')
			smartName += (char) ((tolower(contact.getName()[i]) - 'a' - 1) / 3 + '2');
		else
			smartName += (char) ((tolower(contact.getName()[i]) - 'a' - 2) / 3 + '2');
	}
	//End of conversion
	//cout << smartName << endl;
	Node* temp = root;
	for (unsigned int i = 0; i < smartName.size(); ++i) {
		if (temp->arc[smartName[i] - '0'] == NULL)
			temp->arc[smartName[i] - '0'] = new Node;
		temp = temp->arc[smartName[i] - '0'];
	}
	temp->addContactPointer(contact);
}
//============================================================================//
LinkedList<ContactPointer> Trie::find(string smartName) {
	LinkedList<ContactPointer> res;
	res.delimiter = "\n";
	Node* temp = root;
	for (unsigned int i = 0; i < smartName.size(); ++i) {
		temp = temp->arc[smartName[i] - '0'];
		if (temp == NULL)
			return res;		//res is empty
	}

	//DFSing and adding all LinkedLists
	stack<Node*> S;
	S.push(temp);
	while(!S.empty()) {
		res += S.top()->contacts;
		temp = S.top();
		S.pop();
		for (int i = 0; i < 10; ++i)
			if (temp->arc[i] != NULL)
				S.push(temp->arc[i]);
	}

	return res;
}
//============================================================================//
//============================================================================//


#endif /* TRIE_H_ */
