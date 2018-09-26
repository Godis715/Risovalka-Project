#ifndef __MODELn
#define __MODELn

#include "Model.h"

class ModelNew {
private:
	//ObjectController* objCtrl;
	//PrimController* primCtrl;
	//ReqController* reqCtrl;
	//DataController* dataCtrl;

	static ModelNew* instance;

	ModelNew();
public:
	static ModelNew* GetInstance() {
		return nullptr;
	}

	ID CreatePrimitive(object_type, const Array<double>&) const {
		return ID();
	}
	ID CreateRequirement(object_type, const Array<ID>&, const Array<double>&) const {
		return ID();
	}
	ID GetObjectByClick(double, double) const {
		return ID();
	}

	void ChangeRequirement(const ID&, const Array<double>&) const {}
	void DeleteObject(const ID&) const {}
	void OptimizeByID(const ID&) const {}
	void Scale(const Array<ID>&, const double) const {}
	void Move(const Array<ID>&, const Vector2&) const {}
	void Clear() const {}

	Array<ID> GetObjectsByArea(double, double, double, double) const {
		return Array<ID>();
	}

	object_type GetObjType(const ID&) const {
		return object_type();
	}
	Array<double> GetObjParam(const ID&) const {
		return Array<double>();
	}

	Array<ID> CreatePrimitive() {
		return Array<ID>();
	}

};

#endif