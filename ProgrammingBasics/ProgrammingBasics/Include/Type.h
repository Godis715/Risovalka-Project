#ifndef __TYPE
#define __TYPE

enum type_id { point = 1, segment, arc };

class Type {
private:
	char* name;
	type_id id;
public:
	Type(type_id);
	const char* GetName() const;
	type_id GetTypeId() const;
};

#endif
