#ifndef __IDReq
#define __IDReq

class IDReq {
private:
	unsigned long long hash;
public:
	IDReq(unsigned long long);
	IDReq();
	bool operator== (const IDReq&) const;
	bool operator< (const IDReq&) const;
	bool operator> (const IDReq&) const;
	int operator %(int) const;
};

#endif