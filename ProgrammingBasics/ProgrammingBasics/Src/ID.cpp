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
int ID::operator %(int item) const {
	return this->hash % item;
}
ID::ID() {
	hash = 0;
}

// IDReq FUNCTIONS

IDReq::IDReq(unsigned long long h) {
	hash = h;
}
bool IDReq::operator== (const IDReq& item) const {
	return hash == item.hash;
}
bool IDReq::operator< (const IDReq& item) const {
	return hash < item.hash;
}
bool IDReq::operator> (const IDReq& item) const {
	return hash > item.hash;
}
int IDReq::operator %(int item) const {
	return this->hash % item;
}
IDReq::IDReq() {
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

// IDREQGENERATOR FUNCTIONS

IDReq IDReqGenerator::generateIDReq() {
	return IDReq(++_lastGivenHashReq);
}

IDReqGenerator* IDReqGenerator::getInstance() {
	if (_instance == nullptr) {
		_instance = new IDReqGenerator;
	}
	return _instance;
}

// IDGENERATOR'S STATIC MEMBERS INITIALIZING

unsigned long long IDGenerator::_lastGivenHash = 0;
IDGenerator* IDGenerator::_instance = nullptr;

unsigned long long IDReqGenerator::_lastGivenHashReq = 0;
IDReqGenerator* IDReqGenerator::_instance = nullptr;