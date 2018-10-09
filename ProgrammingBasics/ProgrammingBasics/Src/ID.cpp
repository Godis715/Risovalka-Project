#include "IDGenerator.h"

// ID FUNCTIONS

ID::ID(unsigned long long h) {
	hash = h;
	object = nullptr;
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

ID* IDGenerator::generateID() const {
	return new ID(++_lastGivenHash);
}

ID* IDGenerator::generateID(unsigned long long hash) const {
	if (hash > _lastGivenHash) {
		ID* id = new ID(hash);
		_lastGivenHash = hash + 1;
		return id;
	}
	else {
		LOGERROR("generateID: this hash already used", LEVEL_3);
	}
	
}

ID IDGenerator::GetNullID() {
	return ID(0);
}

bool IDGenerator::IsNullID(const ID& id) {
	return (id.object == nullptr);
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

Object::Object(object_type _type, const Array<double>& _params, const Array<ID>& _children) : 
	type(_type),
	params(_params),
	children(_children)
{
	id = IDGenerator::getInstance()->generateID();
	id->object = this;
	isValid = true;
}

Object::Object(object_type _type, const Array<double>& _params, const Array<ID>& _children, unsigned long long _hash) :
	type(_type),
	params(_params),
	children(_children)
{
	id = IDGenerator::getInstance()->generateID(_hash);
	id->object = this;
	isValid = true;
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

void Object::SetParams(const Array<double>& _params) {
	params = _params;
}

Array<double> Object::GetParams() const {
	return params;
}

Array<ID> Object::GetChildren() const {
	return children;
}
