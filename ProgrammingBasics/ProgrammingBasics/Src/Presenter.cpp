#include "Presenter.h"
#include "Mode.h"

Model* Presenter::model(nullptr);
Mode* Presenter::mode(nullptr);
IView* Presenter::view(nullptr);
//temp
statusCreate Presenter::status(drawCircle);
Array<Vector2> Presenter::posClicks(3);
Array<double> Presenter::params(6);

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

void Presenter::drawScene()
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

	//mode->DrawMode();
}

void  Presenter::changeStatusCreate(const statusCreate newStatus)
{
	status = newStatus;
	posClicks.Clear();
	params.Clear();
	view->Clear();
}

void  Presenter::clearScene()
{
	view->Clear();
	posClicks.Clear();
}

void  Presenter::clickOnScene(double x, double y)
{
	view->SetColor(red);
	view->DrawPoint(Vector2(x, y));
	switch (status)
	{
	case drawPoint:
		params.PushBack(x);
		params.PushBack(y);
		CreateObject(point_t, params);
		params.Clear();
		break;
	case drawSegment:
		params.PushBack(x);
		params.PushBack(y);
		switch (posClicks.GetSize())
		{
		case 0:
			posClicks.PushBack(Vector2(x, y));
			break;
		case 1:
			CreateObject(segment_t, params);
			params.Clear();

			view->SetColor(white);
			view->DrawLine(posClicks[0], Vector2(x, y), line);
			posClicks.Clear();
			break;
		}
		break;
	case drawArc:
		switch (posClicks.GetSize())
		{
		case 0:
			posClicks.PushBack(Vector2(x, y));
			break;
		case 1:
			posClicks.PushBack(Vector2(x, y));

			//..
			view->SetColor(white);
			view->DrawCircle(posClicks[0], posClicks[1], points);
			//..
			break;
		case 2:
			params.PushBack(posClicks[1].x);
			params.PushBack(posClicks[1].y);
			params.PushBack(x);
			params.PushBack(y);
			params.PushBack(Vector2::Angle(posClicks[1] - posClicks[0], Vector2(x, y) - posClicks[0]));
			CreateObject(arc_t, params);
			params.Clear();

			//..
			view->SetColor(black);
			view->DrawCircle(posClicks[0], posClicks[1], points);
			//..

			view->SetColor(white);
			view->DrawArc(posClicks[0], posClicks[1], Vector2(x, y), line);

			view->SetColor(black);
			view->DrawPoint(posClicks[0]);
			posClicks.Clear();
			break;
		}
		break;
	case drawCircle:
		switch (posClicks.GetSize())
		{
		case 0:
			posClicks.PushBack(Vector2(x, y));
			break;
		case 1:
			params.PushBack(posClicks[0].x);
			params.PushBack(posClicks[0].y);
			params.PushBack((Vector2(x, y) - posClicks[0]).GetLength());
			CreateObject(circle_t, params);
			params.Clear();

			view->SetColor(black);
			view->DrawPoint(Vector2(x, y));

			//..
			view->SetColor(white);
			view->DrawCircle(posClicks[0], Vector2(x, y), line);

			posClicks.Clear();
			//..
			break;
		}
		break;
	}
}