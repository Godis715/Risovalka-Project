#include "Presenter.h"
#include "Mode.h"

Model* Presenter::model(nullptr);
Mode* Presenter::mode(nullptr);
IView* Presenter::view(nullptr);
//temp

IView* Presenter::GetView()
{
	return view;
}

void Presenter::Initializer(IView* _view)
{
	view = _view;
	model = new Model();
	mode = new Selection();
}

ID Presenter::CreateObject(object_type type, const Array<double>& params) {
	ID id;
	bool result = model->CreateObject(type, params, id);
	if (!result) {
		throw std::exception("could not create object");
	}
	//
	// possible clear selected Objects
	//
	return id;
	// _selObj.PushBack(id);
}

bool Presenter::CreateRequirement(object_type type, const Array<ID>& objects, const Array<double>& params) {
	ID id;
	bool result = model->CreateRequirementByID(type, objects, params, id);

	return result;
}

//bool Presenter::CreateRequirement(object_type type, const Array<double>& params) {
//	ID id;
//	bool result = model->CreateRequirementByID(type, _selObj, params, id);
//	if (result) {
//	_selReq.PushBack(id);
//	}
//	return result;
//}

void Presenter::DeletePrimitives(const Array<ID>& primitiveID) {
	for (int i = 0; i < primitiveID.GetSize(); ++i) {
		if (!model->DeletePrimitive(primitiveID[i])) {
			// LOG
		}
	}
}

void Presenter::DeleteRequirement(const ID& id) {
	
}

void Presenter::CleareScene() {
	Array<double> temp(0);
	mode->HandleEvent(ev_escape, temp);
	model->Clear();
	view->Update();
}

void Presenter::ChangeParamRequirement(const ID& id, const double param) {
	model->ChangeRequirement(id, param);
}

void Presenter::ScaleObjects(const Array<ID>& primitiveID, const double koef) {
	if (!model->Scale(primitiveID, koef)) {
		// LOG
	}
}

void Presenter::MoveObject(const Array<ID>& primitiveID,const Vector2& vector) {
	if (!model->Move(primitiveID, vector)) {
		// LOG
	}
}

void Presenter::GetComponent(const ID& id, Array<ID>& primID, Array<ID>& reqID) {
	if (!model->NewComponent(id, primID, reqID)) {
		// LOG
	}
}

bool Presenter::GetObject(double x, double y, ID& obj_id) {
	Array<ID> ids;
	Array<object_type> types;
	Array<double> distances;
	bool isFound = model->GetObject(x, y, ids, types, distances);
	if (isFound) {
		if (ids.GetSize() == 0) {
			//LOG!!
			return false;
		}
		bool foundPoint = (types[0] == point_t);
		double minDist = distances[0];
		obj_id = ids[0];
		for (int i = 1; i < distances.GetSize(); ++i) {
			if (types[i] == point_t) {
				if (foundPoint) {
					if (minDist > distances[i]) {
						obj_id = ids[i];
						minDist = distances[i];
					}
				}
				else {
					foundPoint = true;
					obj_id = ids[i];
					minDist = distances[i];
				}
			}
			else {
				if (!foundPoint) {
					if (minDist > distances[i]) {
						obj_id = ids[i];
						minDist = distances[i];
					}
				}
			}
		}
	}
	else {
		return false;
	}
}

void Presenter::DrawScene()
{
	Array<Model::infoObject> scene;
	if (model->DischargeInfoObjects(scene)) {
		for (int i = 0; i < scene.GetSize(); ++i) {
			if (scene[i].type == point_t) {
				view->SetColor(red);
				view->DrawPoint(Vector2(scene[i].params[0], scene[i].params[1]));
			}
			if (scene[i].type == segment_t) {
				view->SetColor(white);
				view->DrawLine(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[2], scene[i].params[3]), line);
			}
			if (scene[i].type == arc_t) {
				view->SetColor(white);
				view->DrawArc(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[2], scene[i].params[3]),
					Vector2(scene[i].params[4], scene[i].params[5]), line);
			}
			if (scene[i].type == circle_t) {
				view->SetColor(white);
				view->DrawCircle(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[0] + scene[i].params[2], scene[i].params[1]), line);
			}
		}
	}
	mode->DrawMode();
}

void Presenter::Set_event(Event _ev, Array<double>& _params)
{
	Mode* temp = mode->HandleEvent(_ev, _params);
	if (temp != nullptr)
	{
		delete mode;
		mode = temp;
	}
	view->Update();
}

bool Presenter::GetObjType(const ID& id, object_type& type)
{
	return model->GetObjType(id, type);
}

bool Presenter::GetObjParam(const ID& id, Array<double>& params)
{
	return model->GetObjParam(id, params);
}

