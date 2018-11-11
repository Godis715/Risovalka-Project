#include "Presenter.h"
#include "Mode.h"

Array<ID> CreatePoint(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 2) {
		return Array<ID>(0);
	}
	ID id = Model::GetInstance()->CreatePrimitive(ot_point, params);
	return CreateArr(id);
}
Array<ID> CreateSegment(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 4) {
		return Array<ID>(0);
	}
	ID id = Model::GetInstance()->CreatePrimitive(ot_segment, params);
	auto res = CreateArr(id);
	res += ObjectController::GetInstance()->GetObjChildren(id);
	return res;
}
Array<ID> CreateArc(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 6) {
		return Array<ID>(0);
	}
	ID id = Model::GetInstance()->CreatePrimitive(ot_arc, params);
	auto res = CreateArr(id);
	res += ObjectController::GetInstance()->GetObjChildren(id);
	return res;
}
Array<ID> CreateCircle(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 3) {
		return Array<ID>(0);
	}
	ID id = Model::GetInstance()->CreatePrimitive(ot_circle, params);
	auto res = CreateArr(id);
	res += ObjectController::GetInstance()->GetObjChildren(id);
	return res;
}
Array<ID> Move(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 2) {
		throw std::exception("invalid arguments");
	}
	Model::GetInstance()->Move(obj, Vector2(params[0], params[1]));
	Model::GetInstance()->Move(obj, Vector2(params[0], params[1]));
	return Array<ID>(0);

}
Array<ID> Scale(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 1) {
		throw std::exception("invalid arguments");
	}
	Model::GetInstance()->Scale(obj, params[0]);
	Model::GetInstance()->Scale(obj, params[0]);
	return Array<ID>(0);
}
Array<ID> DistBetPoints(const Array<ID>& obj, const Array<double>& params) {
	ID id = Model::GetInstance()->CreateRequirement(ot_distBetPoints, obj, params);
	return CreateArr(id);
}
Array<ID> EqualSegment(const Array<ID>& obj, const Array<double>& params) {
	ID id = Model::GetInstance()->CreateRequirement(ot_equalSegmentLen, obj, params);
	return CreateArr(id);
}
Array<ID> DistanceBetPointSegment(const Array<ID>& obj, const Array<double>& params) {
	ID id = Model::GetInstance()->CreateRequirement(ot_distBetPointSeg, obj, params);
	return CreateArr(id);
}
Array<ID> Delete(const Array<ID>& obj, const Array<double>& params) {
	for (int i = 0; i < obj.GetSize(); ++i) {
		DataController::GetInstance()->DeleteObject(obj[i]);
	}
	return Array<ID>(0);
}


Mode* Presenter::mode(nullptr);
IView* Presenter::view(nullptr);
Model* Presenter::model(nullptr);
//temp

IView* Presenter::GetView()
{
	return view;
}

void Presenter::Initializer(IView* _view)
{
	LOG("Initializing presenter", LEVEL_3);
	view = _view;
	mode = new Selection();
	model = Model::GetInstance();
	// BinSearchTree<string, std::function<ID(const Array<ID>&, const Array<double>&)>> kek;
	//std::function<ID(const Array<ID>&, const Array<double>&)> f = [model](const Array<ID>& a, const Array<double>& b) {
	//	model->Move(a, Vector2(b[0], b[1]));
	//	return ID();
	//};
	auto tree = new treeFunc;
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
	model->Clear();
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
void Presenter::MoveObject(const Array<ID>& primitiveID,const Vector2& vector) {
	model->Move(primitiveID, vector);
}

//void Presenter::GetComponent(const ID& id, Array<ID>& primID, Array<ID>& reqID) {
//	if (!Model::GetInstance()->NewComponent(id, primID, reqID)) {
//		LOG(string("could not get new component"), LEVEL_3);
//	}
//}

//bool Presenter::GetObjectsOnArea(double x1, double y1, double x2, double y2, Array<ID>& obj_id)
//{
//	Array<object_type> types;
//	return Model::GetInstance()->GetObjectsOnArea(x1, y1, x2, y2, obj_id, types);
//}

void Presenter::DrawSelectedObjects(const Array<ID>& selectedObjects)
{
	for (int i = 0; i < selectedObjects.GetSize(); i++)
	{
		Array<double> params = model->GetPrimParamsForDrawing(selectedObjects[i]);
		object_type type = model->GetObjType(selectedObjects[i]);

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
			GetView()->DrawArc(Vector2(params[5], params[6]),
				Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
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
	auto objCtrl = ObjectController::GetInstance();
	auto primCtrl = PrimController::GetInstance();
	auto iter = model->GetPrimIterator();
	while (iter.IsValid()) {
		ID obj = *iter;
		++iter;
		if (!objCtrl->IsValid(obj)) {
			continue;
		}
		Array<double> params = model->GetPrimParamsForDrawing(obj);

		if (model->GetObjType(obj) == ot_point) {
			view->SetColor(col_Red);
			view->DrawPoint(Vector2(params[0], params[1]));
		}
		if (model->GetObjType(obj) == ot_segment) {
			view->SetColor(col_White);
			view->DrawLine(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
		}
		if (model->GetObjType(obj) == ot_arc) {
			view->SetColor(col_White);
			view->DrawArc(Vector2(params[5], params[6]),
				Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
		}
		if (model->GetObjType(obj) == ot_circle) {
			view->SetColor(col_White);
			view->DrawCircle(Vector2(params[0], params[1]),
				Vector2(params[0] + params[2], params[1]), line);
		}

	}

	mode->DrawMode();
}

void Presenter::SaveProject(const std::string& path) 
{
	model->Save(path);
}

void Presenter::DownloadFile(const std::string& path)
{
	model->Download(path);
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
