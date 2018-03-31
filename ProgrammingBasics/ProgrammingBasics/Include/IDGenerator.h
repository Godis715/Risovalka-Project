#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include "ID.h"

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

#endif // IDGENERATOR_H
