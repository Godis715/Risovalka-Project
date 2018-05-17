#ifndef __ID
#define __ID

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

#endif