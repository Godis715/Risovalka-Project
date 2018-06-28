#ifndef __ID
#define __ID

#include <iostream>

class ID {
private:
	unsigned long long hash;
public:
	ID(unsigned long long);
	ID();
	void operator=(const ID&);
	bool operator== (const ID&) const;
	bool operator< (const ID&) const;
	bool operator> (const ID&) const;
	unsigned long long GetHash() const;
};

std::ostream& operator<<(std::ostream&, const ID&);


#endif