#ifndef __ID
#define __ID

class ID {
private:
	int hash;
public:
	ID(int);
	bool operator== (ID&);
	bool operator< (ID&);
};

ID::ID(int h) {
	hash = h;
}

bool ID::operator==(ID& item) {
	return hash == item.hash;
}

bool ID::operator<(ID& item) {
	return hash < item.hash;
}

#endif