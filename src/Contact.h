#ifndef CONTACT_H_
#define CONTACT_H_

#include "LinkedList.h"
#include <string>
using namespace std;

class Contact {
private:
        string name;
        LinkedList<string> phone_numbers;
public:
        Contact();
        Contact(string name);
        void addPhoneNumber(string number);
        string getName();
        bool operator<(const Contact & c);
        bool operator==(const Contact & c);
        friend ostream& operator<<(ostream& o, const Contact & c);
        friend ostream& operator<<(ostream& o, Contact* c);
};

//=================================================================
Contact::Contact() {
    phone_numbers.delimiter = " - ";
}
//=================================================================
Contact::Contact(string name) {
	phone_numbers.delimiter = " - ";
	this->name = name;
}
//=================================================================
void Contact::addPhoneNumber(string number) {
	this->phone_numbers.addSorted(number);
}
//=================================================================
string Contact::getName() {
	return this->name;
}
//=================================================================
bool Contact::operator<(const Contact& c) {
	return this->name < c.name;
}
//=================================================================
bool Contact::operator==(const Contact& c) {
	return this->name == c.name;
}
//=================================================================
ostream& operator<<(ostream& o, const Contact & c) {
	o << c.name << ": ";
	o << c.phone_numbers;
	return o;
}
//=================================================================

#endif  /* CONTACT_H_ */
