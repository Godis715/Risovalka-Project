#include "IDGenerator.h"

// ID FUNCTIONS

ID::ID(unsigned long long h) {
	hash = h;
#ifdef MODEL_VERSION_DATA
	index = -1;
#endif
}
void ID::operator= (const ID& item) {
	hash = item.hash;
#ifdef MODEL_VERSION_DATA
	index = item.hash;
#endif
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
ID::ID() {
#ifdef MODEL_VERSION_DATA
	index =-1;
#endif
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