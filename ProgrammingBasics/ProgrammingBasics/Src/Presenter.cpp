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
	LOG(string("Initializing presenter"), LEVEL_3);
	view = _view;
	model = new Model();
	mode = new Selection();
}

ID Presenter::CreateObject(object_type type, const Array<double>& params) {
	ID id;
	LOG(string("Presenter::Creating object"), LEVEL_1);
	bool result = model->CreateObject(type, params, id);
	if (!result) {
		LOG(string("Presenter::Could not create object"), LEVEL_3);
		// $$$ throw std::runtime_error("could not create object");
	}
	LOG(string("Presenter::Created object"), id, LEVEL_1);
	return id;
}

ID Presenter::CreateRequirement(object_type type, const Array<ID>& objects, const Array<double>& params) {
	ID id;
	LOG(string("Presenter::Creating requirement"), LEVEL_1);
	bool result = model->CreateRequirementByID(type, objects, params, id);
	if (!result) {
		LOG(string("Presenter::Could not create requirement"), LEVEL_3);
	}

	return id;
}

void Presenter::DeletePrimitives(const Array<ID>& primitiveID) {
	for (int i = 0; i < primitiveID.GetSize(); ++i) {
		if (!model->DeletePrimitive(primitiveID[i])) {
			LOG(string("could not delete prim"), primitiveID[i], LEVEL_3);
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
		LOG(string("could not Scale prim"), LEVEL_3);
	}
}

void Presenter::MoveObject(const Array<ID>& primitiveID,const Vector2& vector) {
	if (!model->Move(primitiveID, vector)) {
		LOG(string("could not move prim"), LEVEL_3);
	}
}

void Presenter::GetComponent(const ID& id, Array<ID>& primID, Array<ID>& reqID) {
	if (!model->NewComponent(id, primID, reqID)) {
		LOG(string("could not get new component"), LEVEL_3);
	}
}

bool Presenter::GetObject(double x, double y, ID& obj_id) {
	Array<ID> ids;
	Array<object_type> types;
	Array<double> distances;
	bool isFound = model->GetObject(x, y, ids, types, distances);
	if (isFound) {
		if (ids.GetSize() == 0) {
			LOG(string("could not find primitives by point"), LEVEL_1);
			return false;
		}
		bool foundPoint = (types[0] == ot_point);
		double minDist = distances[0];
		obj_id = ids[0];
		for (int i = 1; i < distances.GetSize(); ++i) {
			if (types[i] == ot_point) {
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

bool Presenter::GetObjectsOnArea(double x1, double y1, double x2, double y2, Array<ID>& obj_id)
{
	Array<object_type> types;
	return model->GetObjectsOnArea(x1, y1, x2, y2, obj_id, types);
}

void Presenter::DrawSelectedObjects(const Array<ID>& selectedObjects)
{
	for (int i = 0; i < selectedObjects.GetSize(); i++)
	{
		Array<double> params;
		object_type type;

		GetObjParam(selectedObjects[i], params);
		GetObjType(selectedObjects[i], type);

		switch (type)
		{
		case ot_point:
			GetView()->SetColor(green);
			GetView()->DrawPoint(Vector2(params[0], params[1]));
			break;
		case ot_segment:
			GetView()->SetColor(green);
			GetView()->DrawLine(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
			break;
		case ot_arc:
			GetView()->SetColor(green);
			GetView()->DrawArc(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]),
				Vector2(params[4], params[5]), line);
			break;
		case ot_circle:
			GetView()->SetColor(green);
			GetView()->DrawCircle(Vector2(params[0], params[1]),
				Vector2(params[0] + params[2], params[1]), line);
			break;
		}
	}
}

void Presenter::DrawScene()
{
	Array<Model::infoObject> scene;
	if (model->DischargeInfoObjects(scene)) {
		for (int i = 0; i < scene.GetSize(); ++i) {
			if (scene[i].type == ot_point) {
				view->SetColor(red);
				view->DrawPoint(Vector2(scene[i].params[0], scene[i].params[1]));
			}
			if (scene[i].type == ot_segment) {
				view->SetColor(white);
				view->DrawLine(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[2], scene[i].params[3]), line);
			}
			if (scene[i].type == ot_arc) {
				view->SetColor(white);
				view->DrawArc(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[2], scene[i].params[3]),
					Vector2(scene[i].params[4], scene[i].params[5]), line);
			}
			if (scene[i].type == ot_circle) {
				view->SetColor(white);
				view->DrawCircle(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[0] + scene[i].params[2], scene[i].params[1]), line);
			}
		}
	}
	mode->DrawMode();
}

void Presenter::SaveProject(std::string way) 
{
	model->SaveProject(way);
}

void Presenter::DownloadFile(std::string nameFile)
{
	model->DownloadFile(nameFile);
	view->Update();
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
