#ifndef __ID
#define __ID

class ID {
private:
	unsigned long long hash;
public:
	ID(unsigned long long);
	ID();
	bool operator== (const ID&) const;
	bool operator< (const ID&) const;
	bool operator> (const ID&) const;
	//int operator %(int) const;
	unsigned long long GetHash() const;
};

#endif