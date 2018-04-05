#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include "ID.h"
#include "IDReq.h"

class IDGenerator
{
	public:
	static IDGenerator * getInstance();

		ID generateID();
	private:
		IDGenerator() { }
		static IDGenerator* _instance;

	static unsigned long long _lastGivenHash;
};

class IDReqGenerator
{
public:
	static IDReqGenerator * getInstance();

	IDReq generateIDReq();
private:
	IDReqGenerator() { }
	static IDReqGenerator* _instance;

	static unsigned long long _lastGivenHashReq;
};


#endif // IDGENERATOR_H
