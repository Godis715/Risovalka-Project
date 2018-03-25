#ifndef __ID
#define __ID

class ID {
private:
	unsigned long long hash;
public:
	ID(unsigned long long);
	ID();
	bool operator== (ID&);
	bool operator< (ID&);
};

ID::ID(unsigned long long h) {
	hash = h;
}

bool ID::operator==(ID& item) {
	return hash == item.hash;
}

bool ID::operator<(ID& item) {
	return hash < item.hash;
}

ID::ID() {
	hash = 0;
}

#endif