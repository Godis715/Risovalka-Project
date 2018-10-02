#ifndef __MODEL
#define __MODEL

#include "Requirement.h"
#include "Primitives.h"
#include "Optimizer.h"
#include "DataController.h"

class Model {
private:
	ObjectController* objCtrl;
	PrimController* primCtrl;
	ReqController* reqCtrl;
	DataController* dataCtrl;

	static Model* instance;

	Model();
public:
	static Model* GetInstance();

	ID CreatePrimitive(object_type, const Array<double>&) const;
	ID CreateRequirement(object_type, const Array<ID>&, const Array<double>&) const;

	#define SEARCHING_AREA 5.0
	ID GetObjectByClick(double, double) const;

	void ChangeRequirement(const ID&, const Array<double>&) const;
	void DeleteObject(const ID&) const;
	void OptimizeByID(const ID&) const;
	void Scale(const Array<ID>&, const double) const;
	void Move(const Array<ID>&, const Vector2&) const;
	void Clear() const;

	bool IsPrim(const ID&) const;
	bool IsReq(const ID&) const;


	Array<ID> GetObjectsByArea(double, double, double, double) const;
	Component GetComponent(const ID&);

	object_type GetObjType(const ID&) const;
	Array<double> GetObjParam(const ID&) const;
	Array<double> GetPrimParamsForDrawing(const ID&) const;

	BinSearchTree<ID, ID>::bst_iterator GetPrimIterator();
};

#endif