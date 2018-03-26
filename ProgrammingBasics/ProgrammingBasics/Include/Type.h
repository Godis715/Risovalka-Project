#ifndef __TYPE
#define __TYPE

#include <string>

enum type_id { point = 1, segment, arc };

class Type {
private:
	std::string name;
	type_id id;
public:
	Type(type_id);
	std::string GetName() const;
	type_id GetTypeId() const;
};

#endif
