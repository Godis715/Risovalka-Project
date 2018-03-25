#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include "ID.h"

class IDGenerator
{
	public:
	static IDGenerator * getInstance(){
			if (_instance == nullptr )
				_instance  = new IDGenerator;
			return _instance;
		};

		ID generateID();
	private:
	IDGenerator();
	static IDGenerator* _instance;

	static unsigned long long _lastGivenHash;
};

ID IDGenerator::generateID() {
	return ID(_lastGivenHash++);
}

unsigned long long IDGenerator::_lastGivenHash = 1;
IDGenerator* IDGenerator::_instance = nullptr;

#endif // IDGENERATOR_H
