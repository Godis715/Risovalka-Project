#include "IDGenerator.h"

// ID FUNCTIONS

ID::ID(unsigned long long h) {
	hash = h;
}
ID::ID() {
	hash = 0;
	object = nullptr;
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

ID* IDGenerator::generateID() {
	return new ID(++_lastGivenHash);
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

// 

void PrimitivesController::ChangeParams(ID& id, const Array<double>&) const {
	
}

Object::Object(object_type _type) : type(_type) {
	id = IDGenerator::getInstance()->generateID();
}
Object::~Object() {
	delete id;
}
object_type Object::GetType() const {
	return type;
}
ID Object::GetID() const {
	return *id;
}