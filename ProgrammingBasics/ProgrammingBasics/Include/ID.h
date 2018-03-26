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

#endif