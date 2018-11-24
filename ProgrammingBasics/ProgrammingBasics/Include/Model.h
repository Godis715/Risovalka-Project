#ifndef __MODEL
#define __MODEL

#include "Requirement.h"
#include "Primitives.h"
#include "Optimizer.h"
#include "DataController.h"
#include "Compilator.h"
#include "Undo-Redo.h"

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
	ID AddPointToCurve(const ID&, const int, const Array<double>&) const;
	Array<ID> OrderedCreateRequirement(const Array<ID>& id_arr) const;
	ID CreateRequirement(object_type, const Array<ID>&, const Array<double>&) const;


	ID GetObjectByClick(double, double) const;
	Array<ID> GetObjectsByArea(double, double, double, double) const;

	// with optimization
	void ChangeRequirement(const ID&, const Array<double>&) const;
	
	void DeleteObject(ID&) const;
	void DeleteObjects(Array<ID>&) const;

	void OptimizeByID(const ID&) const;
	void Optimize() const;
	void CashNewComponent(const Array<ID>&) const;
	void Scale(const Array<ID>&, const double) const;
	void Move(const Array<ID>&, const Vector2&) const;
	void Rotate(const Array<ID>& objs, const double) const;
	void Rotate(const Array<ID>& objs, const Vector2&, const double) const;
	void Clear() const;

	void Save(const std::string&) const;
	void Download(const std::string&) const;

	bool IsPrim(const ID&) const;
	bool IsReq(const ID&) const;

	Array<ID> GetRelatedObjects(const ID&) const;

	Component GetComponent(const ID&);

	object_type GetObjType(const ID&) const;
	Array<double> GetObjParam(const ID&) const;
	void SetVariableObjParam(const ID&, const Array<double>&, int...) const;
	Array<double> GetVariableObjParam(const ID&, int...) const;
	Array<double> GetPrimParamsForDrawing(const ID&) const;

	Set<ID>::bst_iterator GetPrimIterator();
};

#endif