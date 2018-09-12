#include "IDGenerator.h"

// ID FUNCTIONS

ID::ID(unsigned long long h, Object* obj) {
	hash = h;
	object = obj;
}
ID::ID() {
	hash = 0;
	object = nullptr;
}
ID::ID(const ID& _id) {
	hash = _id.hash;
	object = _id.object;
}
ID::~ID() { }
void ID::operator= (const ID& item) {
	hash = item.hash;
	object = item.object;
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

ID* IDGenerator::generateID(Object* obj) {
	ID* id = new ID(++_lastGivenHash, obj);
	return id;
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

Object::Object(object_type _type) : type(_type) {
	id = IDGenerator::getInstance()->generateID(this);
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