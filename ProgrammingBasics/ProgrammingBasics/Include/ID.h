#ifndef __ID
#define __ID

#define MODEL_VERSION_LINK

class ID {
private:
	unsigned long long hash;
public:
#ifdef MODEL_VERSION_DATA
	int index;
#endif

	ID(unsigned long long);
	ID();
	void operator=(const ID&);
	bool operator== (const ID&) const;
	bool operator< (const ID&) const;
	bool operator> (const ID&) const;
	unsigned long long GetHash() const;
};

#endif