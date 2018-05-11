#include "Presenter.h"



void Presenter::CreateObject(object_type type, const Array<double>& params) {
	ID id;
	model->CreateObject(type, params, id);
	selectedObjects.Add(id, id);
	// _selObj.PushBack(id);
}

bool Presenter::CreateRequirement(object_type type, const Array<double>& params) {
	ID id;
	Array<ID> objects(selectedObjects.GetSize());

	int index = 0;
	for (auto i = selectedObjects.GetMarker(); i.IsValid(); ++i) {
		objects[index] = i.GetValue();
		++index;
	}
	bool result = model->CreateRequirementByID(type, objects, params, id);
	selectedReq.Add(id, id);

	return result;
}

//bool Presenter::CreateRequirement(object_type type, const Array<double>& params) {
//	ID id;
//	bool result = model->CreateRequirementByID(type, _selObj, params, id);
//	_selReq.PushBack(id);
//
//	return result;
//}

void Presenter::DeleteRequirement(int index) {
	// ID id = _selReq[index];
	// model->DeleteRequirement(id);
	auto marker = selectedObjects.GetMarker();
	for (auto i = selectedObjects.GetMarker(); i.IsValid; ++i) {
		if (index == 0) {
			model->DeleteRequirement(i.GetValue());
			return;
		}
		--index;
	}
}

void Presenter::DeletePrimitives() {
	/*for (int i = 0; i < _selObj.GetSize(); ++i) {
		model->DeletePrimitive(_selObj[i]);
	}*/
	for (auto i = selectedObjects.GetMarker(); i.IsValid(); ++i) {
		model->DeletePrimitive(i.GetValue());
	}
}

void Presenter::ChangeParamRequirement(int index, const double param) {
	// model->FFF(_selReq[index], param);
	auto marker = selectedObjects.GetMarker();
	for (auto i = selectedObjects.GetMarker(); i.IsValid; ++i) {
		if (index == 0) {
			model->ChangeRequirement(i.GetValue(), param);
			return;
		}
		--index;
	}
}

void Presenter::ScaleObject(const double koef) {
	// model->Scale(_selObj, koef);
	
	Array<ID> objects(selectedObjects.GetSize());

	int index = 0;
	for (auto i = selectedObjects.GetMarker(); i.IsValid(); ++i) {
		objects[index] = i.GetValue();
		++index;
	}
	// model->Scale(objects, koef);
	
}

void Presenter::MoveObject(const Vector2& vector) {
	// model->Move(_selObj, vector);

	Array<ID> objects(selectedObjects.GetSize());

	int index = 0;
	for (auto i = selectedObjects.GetMarker(); i.IsValid(); ++i) {
		objects[index] = i.GetValue();
		++index;
	}
	// model->Move(objects, vector);

}

void Presenter::GetRequirements() {
	Array<ID> reqs;
	ID id = selectedObjects.GetMarker().GetValue();
	// ID id = _selObj[0];

	// model->GetRequirements(id, reqs);
}


//void Prese