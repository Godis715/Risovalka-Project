#ifndef __MODEL
#define __MODEL

#include "Requirement.h"
#include "Primitives.h"
#include "DataController.h"

class ClassName {
private:
	ObjectController* objCtrl;
	PrimController* primCtrl;
	ReqController* reqCtrl;
	DataController* dataCtrl;

	static ClassName* instance;

	ClassName();
public:
	ClassName* GetInstance();

	ID CreatePrimitive(object_type, const Array<double>&);
	ID CreateRequirement(object_type, const Array<ID>&, const Array<double>&);
	ID GetObjectByClick(double, double);

	void ChangeRequirement(const ID&, const Array<double>&);
	void DeleteObject(const ID&);
	void OptimizeByID(const ID&);
	void Scale(const Array<ID>&, const double);
	void Move(const Array<ID>&, const Vector2&);
	void Clear();

	Array<ID> GetObjectsByArea(double, double, double, double);

	object_type GetObjType(const ID&);
	Array<double> GetObjParam(const ID&);

	Array<ID> CreatePrimitive();  // fs
};

#endif