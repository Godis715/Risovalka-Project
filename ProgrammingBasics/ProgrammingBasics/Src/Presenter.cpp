#include "Presenter.h"
#include "Mode.h"

ID CreatePoint(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreatePrimitive(ot_point, params);
	Model::GetInstance()->CreateObject(ot_point, params, id);
	return id;
}
ID CreateSegment(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreatePrimitive(ot_segment, params);
	Model::GetInstance()->CreateObject(ot_segment, params, id);
	return id;
}
ID CreateArc(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreatePrimitive(ot_arc, params);
	Model::GetInstance()->CreateObject(ot_arc, params, id);
	return id;
}
ID CreateCircle(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreatePrimitive(ot_circle, params);
	Model::GetInstance()->CreateObject(ot_circle, params, id);
	return id;
}
ID Move(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 2) {
		throw std::exception("invalid arguments");
	}
	ModelNew::GetInstance()->Move(obj, Vector2(params[0], params[1]));
	Model::GetInstance()->Move(obj, Vector2(params[0], params[1]));
	return ID();

}
ID Scale(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 1) {
		throw std::exception("invalid arguments");
	}
	ModelNew::GetInstance()->Scale(obj, params[0]);
	Model::GetInstance()->Scale(obj, params[0]);
	return ID();
}
ID DistBetPoints(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreateRequirement(ot_distBetPoints, obj, params);
	Model::GetInstance()->CreateRequirementByID(ot_distBetPoints, obj, params, id);
	return id;
}
ID EqualSegment(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreateRequirement(ot_equalSegmentLen, obj, params);
	Model::GetInstance()->CreateRequirementByID(ot_equalSegmentLen, obj, params, id);
	return id;
}
ID DistanceBetPointSegment(const Array<ID>& obj, const Array<double>& params) {
	ID id = ModelNew::GetInstance()->CreateRequirement(ot_distBetPointSeg, obj, params);
	Model::GetInstance()->CreateRequirementByID(ot_distBetPointSeg, obj, params, id);
	return id;
}
ID Delete(const Array<ID>& obj, const Array<double>& params) {
	ModelNew::GetInstance()->DeleteObjects(obj);
	Model::GetInstance()->DeletePrimitives(obj);
	return ID();
}


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
	mode = new Selection();
	// BinSearchTree<string, std::function<ID(const Array<ID>&, const Array<double>&)>> kek;
	//std::function<ID(const Array<ID>&, const Array<double>&)> f = [model](const Array<ID>& a, const Array<double>& b) {
	//	model->Move(a, Vector2(b[0], b[1]));
	//	return ID();
	//};
	kek* tree = new kek;
	tree->Add("Create_point", CreatePoint);
	tree->Add("Create_segment", CreateSegment);
	tree->Add("Create_arc", CreateArc);
	tree->Add("Create_circle", CreateCircle);
	tree->Add("Move", Move);
	tree->Add("Scale", Scale);
	tree->Add("Dist_bet_points", DistBetPoints);
	tree->Add("Equal_segment", EqualSegment);
	tree->Add("Distance_bet_point_segment", DistanceBetPointSegment);
	tree->Add("Delete", Delete);
	Compiler::Initializer(tree);

}

//ID Presenter::CreateObject(object_type type, const Array<double>& params) {
//	ID id;
//	LOG(string("Presenter::Creating object"), LEVEL_1);
//	bool result = model->CreateObject(type, params, id);
//	if (!result) {
//		LOG(string("Presenter::Could not create object"), LEVEL_3);
//		// $$$ throw std::runtime_error("could not create object");
//	}
//	LOG(string("Presenter::Created object"), id, LEVEL_1);
//	return id;
//}

//ID Presenter::CreateRequirement(object_type type, const Array<ID>& objects, const Array<double>& params) {
//	ID id;
//	LOG(string("Presenter::Creating requirement"), LEVEL_1);
//	bool result = model->CreateRequirementByID(type, objects, params, id);
//	if (!result) {
//		LOG(string("Presenter::Could not create requirement"), LEVEL_3);
//	}
//
//	return id;
//}

void Presenter::CleareScene() {
	Array<double> temp(0);
	mode->HandleEvent(ev_escape, temp);
	Model::GetInstance()->Clear();
	view->Update();
}

//void Presenter::ChangeParamRequirement(const ID& id, const double param) {
//	Model::GetInstance()->ChangeRequirement(id, param);
//}
//
//void Presenter::ChangeParamPrimitive(const ID& id, Array<double>& params)
//{
//	Model::GetInstance()->ChangePrimitive(id, params);
//}
//
//void Presenter::ScaleObjects(const Array<ID>& primitiveID, const double koef) {
//	if (!Model::GetInstance()->Scale(primitiveID, koef)) {
//		LOG(string("could not Scale prim"), LEVEL_3);
//	}
//}
//
//void Presenter::MoveObject(const Array<ID>& primitiveID,const Vector2& vector) {
//	if (!Model::GetInstance()->Move(primitiveID, vector)) {
//		LOG(string("could not move prim"), LEVEL_3);
//	}
//}
//
//void Presenter::GetComponent(const ID& id, Array<ID>& primID, Array<ID>& reqID) {
//	if (!Model::GetInstance()->NewComponent(id, primID, reqID)) {
//		LOG(string("could not get new component"), LEVEL_3);
//	}
//}

bool Presenter::GetObject(double x, double y, ID& obj_id) {
	Array<ID> ids;
	Array<object_type> types;
	Array<double> distances;
	bool isFound = Model::GetInstance()->GetObject(x, y, ids, types, distances);
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

//bool Presenter::GetObjectsOnArea(double x1, double y1, double x2, double y2, Array<ID>& obj_id)
//{
//	Array<object_type> types;
//	return Model::GetInstance()->GetObjectsOnArea(x1, y1, x2, y2, obj_id, types);
//}

void Presenter::DrawSelectedObjects(const Array<ID>& selectedObjects)
{
	for (int i = 0; i < selectedObjects.GetSize(); i++)
	{
		Array<double> params;
		object_type type;
		Model::GetInstance()->GetObjParam(selectedObjects[i], params);
		Model::GetInstance()->GetObjType(selectedObjects[i], type);
		switch (type)
		{
		case ot_point:
			GetView()->DrawPoint(Vector2(params[0], params[1]));
			break;
		case ot_segment:
			GetView()->DrawLine(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
			break;
		case ot_arc:
			GetView()->DrawArc(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]),
				Vector2(params[4], params[5]), line);
			break;
		case ot_circle:
			GetView()->DrawCircle(Vector2(params[0], params[1]),
				Vector2(params[0] + params[2], params[1]), line);
			break;
		}
	}
}

void Presenter::DrawScene()
{
	Array<Model::infoObject> scene;
	if (Model::GetInstance()->DischargeInfoObjects(scene)) {
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
	Model::GetInstance()->SaveProject(way);
}

void Presenter::DownloadFile(std::string nameFile)
{
	Model::GetInstance()->DownloadFile(nameFile);
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

//void Presenter::GetRequirementsByID(const ID& id, Array<ID>& reqIDs)
//{
//	Model::GetInstance()->GetRequirementsByID(id, reqIDs);
//}

//bool Presenter::GetObjType(const ID& id, object_type& type)
//{
//	return Model::GetInstance()->GetObjType(id, type);
//}
//
//bool Presenter::GetObjParam(const ID& id, Array<double>& params)
//{
//	return Model::GetInstance()->GetObjParam(id, params);
//}

void Presenter::Compile() {

	Compiler* compiler = Compiler::GetInstance();
	std::ifstream file;
	file.open("script.txt");
	if (file.is_open()) {
		if (!file.eof()) {
			compiler->Parse(file);
		}
		file.close();
	}
	view->Update();
}
