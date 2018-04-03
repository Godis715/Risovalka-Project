#include "IDGenerator.h"

// ID FUNCTIONS

ID::ID(unsigned long long h) {
	hash = h;
}
bool ID::operator== (const ID& item) const {
	return hash == item.hash;
}
bool ID::operator< (const ID& item) const {
	return hash < item.hash;
}
bool ID::operator> (const ID& item) const {
	return hash > item.hash;
}
int ID::operator %(int value) const {
	return this->hash % value;
}
ID::ID() {
	hash = 0;
}

// IDGENERATOR FUNCTIONS

ID IDGenerator::generateID() {
	return ID(++_lastGivenHash);
}

IDGenerator* IDGenerator::getInstance() {
	if (_instance == nullptr) {
		_instance = new IDGenerator;
	}
	return _instance;
}

// IDGENERATOR'S STATIC MEMBERS INITIALIZING

unsigned long long IDGenerator::_lastGivenHash = 0;
IDGenerator* IDGenerator::_instance = nullptr;
