#pragma once

#include "IDGenerator.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>

class IMarker {
protected:
	bool isValid;
public:
	// virtual T GetValue() const = 0;
	virtual bool MoveNext() = 0;
	//virtual void DeleteCurrent() = 0;
	virtual bool IsValid() const {
		return isValid;
	}
};

class INumerable {
private:
public:
	virtual size_t GetSize() const = 0;
};