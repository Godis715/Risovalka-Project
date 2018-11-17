#include "Presenter.h"
#include "Mode.h"

ID CreatePoint(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateObject(ot_point, params);
}
ID CreateSegment(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateObject(ot_segment, params);
}
ID CreateArc(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateObject(ot_arc, params);
}
ID CreateCircle(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateObject(ot_circle, params);
}
ID Move(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 2) {
		throw std::exception("invalid arguments");
	}
	Presenter::MoveObject(obj, Vector2(params[0], params[1]));
	return ID();

}
ID Scale(const Array<ID>& obj, const Array<double>& params) {
	if (params.GetSize() != 1) {
		throw std::exception("invalid arguments");
	}
	Presenter::ScaleObjects(obj, params[0]);
	return ID();
}
ID DistBetPoints(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateRequirement(ot_distBetPoints, obj, params);
}
ID EqualSegment(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateRequirement(ot_equalSegmentLen, obj, params);
}
ID DistanceBetPointSegment(const Array<ID>& obj, const Array<double>& params) {
	return Presenter::CreateRequirement(ot_distBetPointSeg, obj, params);
}
ID Delete(const Array<ID>& obj, const Array<double>& params) {
	Presenter::DeletePrimitives(obj);
	return ID();
}


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
	LOG("Initializing presenter", LEVEL_3);
	view = _view;
	model = Model::GetInstance();
	mode = new Selection();
	// BinSearchTree<string, std::function<ID(const Array<ID>&, const Array<double>&)>> kek;
	//std::function<ID(const Array<ID>&, const Array<double>&)> f = [model](const Array<ID>& a, const Array<double>& b) {
	//	model->Move(a, Vector2(b[0], b[1]));
	//	return ID();
	//};

	/*kek* tree = new kek;
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
	Compiler::Initializer(tree);*/

}

ID Presenter::CreateObject(object_type type, const Array<double>& params) {
	return model->CreatePrimitive(type, params);
}

ID Presenter::CreateRequirement(object_type type, const Array<ID>& objects, const Array<double>& params) {
	return model->CreateRequirement(type, objects, params);
}

void Presenter::DeletePrimitives(const Array<ID>& primitiveID) {
	for (int i = 0; i < primitiveID.GetSize(); ++i) {
		model->DeleteObject(primitiveID[i]);
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
	model->Scale(primitiveID, koef);
}

void Presenter::MoveObject(const Array<ID>& primitiveID,const Vector2& vector) {
	model->Move(primitiveID, vector);
}

void Presenter::GetComponent(const ID& id, Array<ID>& primID, Array<ID>& reqID) {
	Component comp = model->GetComponent(id);
	auto it = comp.GetMarker();
	while (it.IsValid()) {
		if (model->IsPrim(*it)) {
			primID.PushBack(*it);
		}
		else if(model->IsReq(*it)) {
			reqID.PushBack(*it);
		}
		else {
			//ERROR
		}
		++it;
	}
}

bool Presenter::GetObject(double x, double y, ID& obj_id) {
	ID obj = model->GetObjectByClick(x, y);
	if (obj == IDGenerator::GetNullID()) {
		return false;
	}
	else {
		obj_id = obj;
	}
}

bool Presenter::GetObjectsOnArea(double x1, double y1, double x2, double y2, Array<ID>& obj_id)
{
	obj_id = model->GetObjectsByArea(x1, y1, x2, y2);
	return (obj_id.GetSize() != 0);
}

void Presenter::DrawSelectedObjects(const Array<ID>& selectedObjects)
{
	for (int i = 0; i < selectedObjects.GetSize(); i++)
	{

		Array<double> params = model->GetPrimParamsForDrawing(selectedObjects[i]);
		object_type type = model->GetObjType(selectedObjects[i]);

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
			GetView()->DrawArc(Vector2(params[5], params[6]),
				Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
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
	auto primCtrl = PrimController::GetInstance();
	auto iter = model->GetPrimIterator();
	while (iter.IsValid()) {
		ID obj = *iter;
		Array<double> params = model->GetPrimParamsForDrawing(obj);

		if (model->GetObjType(obj) == ot_point) {
			view->SetColor(red);
			view->DrawPoint(Vector2(params[0], params[1]));
		}
		if (model->GetObjType(obj) == ot_segment) {
			view->SetColor(white);
			view->DrawLine(Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
		}
		if (model->GetObjType(obj) == ot_arc) {
			view->SetColor(white);
			view->DrawArc(Vector2(params[5], params[6]),
				Vector2(params[0], params[1]),
				Vector2(params[2], params[3]), line);
		}
		if (model->GetObjType(obj) == ot_circle) {
			view->SetColor(white);
			view->DrawCircle(Vector2(params[0], params[1]),
				Vector2(params[0] + params[2], params[1]), line);
		}
		++iter;
	}

	mode->DrawMode();
}

void Presenter::SaveProject(std::string way) 
{
	//model->Save(way);
}

void Presenter::DownloadFile(std::string nameFile)
{
	//model->Download(nameFile);
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
	type = model->GetObjType(id);
	return true;
}

bool Presenter::GetObjParam(const ID& id, Array<double>& params)
{
	params = model->GetObjParam(id);
	return true;
}

void Presenter::Compile() {

	/*Compiler* compiler = Compiler::GetInstance();
	std::ifstream file;
	file.open("script.txt");
	if (file.is_open()) {
		if (!file.eof()) {
			compiler->Parse(file);
		}
	}*/
}
