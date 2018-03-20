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

Type::Type(const type_id _id) {
	switch (_id)
	{
	case point: {
		name = "Point";
		break;
	}
	case segment: {
		name = "Segment";
		break;
	}
	case arc: {
		name = "Arc";
		break;
	}
	default:
		/*throw unknown type_id*/
		break;
	}
	id = _id;
}

const char* Type::GetName() const {
	return name;
}

type_id Type::GetTypeId() const {
	return id;
}

#endif