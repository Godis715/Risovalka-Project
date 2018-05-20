#include "IDGenerator.h"

// ID FUNCTIONS

ID::ID(unsigned long long h) {
	hash = h;
}
ID::ID() {
	hash = 0;
}
void ID::operator= (const ID& item) {
	hash = item.hash;
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
unsigned long long ID::GetHash() const {
	return hash;
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

std::ostream& operator<<(std::ostream& out, const ID& id) {
	out << "#" << id.GetHash();
	return out;
}


// IDGENERATOR'S STATIC MEMBERS INITIALIZING

unsigned long long IDGenerator::_lastGivenHash = 0;
IDGenerator* IDGenerator::_instance = nullptr;