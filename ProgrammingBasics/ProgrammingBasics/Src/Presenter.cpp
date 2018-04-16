#include "Presenter.h"
#include "Controller.h"

void Presenter::DrawScene() {
	view->Clear();
	view->SetColor(white);
	Array<Model::infoObject> scene;
	if (model->DischargeInfoObjects(scene)) {
		for (int i = 0; i < scene.GetSize(); ++i) {
			if (scene[i].type == segment) {
				view->DrawLine(Vector2(scene[i].params[0], scene[i].params[1]),
					Vector2(scene[i].params[2], scene[i].params[3]));
			}
			if (scene[i].type == point) {
				view->DrawPoint(Vector2(scene[i].params[0], scene[i].params[1]));
			}
		}
	}

	for (int i = 0; i < controller->buttons.GetSize(); ++i) {

		view->DrawLine(controller->buttons[i].leftUp,
			Vector2(controller->buttons[i].leftUp.x, controller->buttons[i].rightDown.y));
		view->DrawLine(controller->buttons[i].leftUp,
			Vector2(controller->buttons[i].rightDown.x, controller->buttons[i].leftUp.y));
		view->DrawLine(controller->buttons[i].rightDown,
			Vector2(controller->buttons[i].leftUp.x, controller->buttons[i].rightDown.y));
		view->DrawLine(controller->buttons[i].rightDown,
			Vector2(controller->buttons[i].rightDown.x, controller->buttons[i].leftUp.y));
	}

	view->SetColor(red);
	for (int i = 0; i < controller->clickedPoints.GetSize(); ++i) {
		view->DrawPoint(controller->clickedPoints[i]);
	}
	for (int i = 0; i < controller->selectedObjects.GetSize(); ++i) {
		type_id type;
		model->getObjType(controller->selectedObjects[i], type);
		Array<double> params;
		model->getObjParam(controller->selectedObjects[i], params);
		switch (type) {
		case point: {
			Vector2 pos(params[0], params[1]);
			view->DrawPoint(pos);
			break;
		}
		case segment: {
			Vector2 pos1(params[0], params[1]);
			Vector2 pos2(params[2], params[3]);
			view->DrawLine(pos1, pos2);
			break;
		}
		}
		// drawing selected object
	}
}
ID Presenter::CreatePoint(double x, double y) {
	Array<double> params;
	params.PushBack(x);
	params.PushBack(y);

	ID id;
	model->createObject(point, params, id);
	return id;
}
ID Presenter::CreateSegment(double x1, double y1, double x2, double y2) {
	ID id;
	Array<double> params;
	params.PushBack(x1);
	params.PushBack(y1);
	params.PushBack(x2);
	params.PushBack(y2);
	model->createObject(segment, params, id);
	return id;
}
ID Presenter::CreateSegment(ID& p1ID, ID& p2ID) {
	ID id;
	model->createSegment(p1ID, p2ID, id);
	return id;
}
/*ID Presenter::CreateSegment(ID& point1, ID& point2) {
ID id;
model->createSegment(point1, point2, id);
return id;
}*/
ID Presenter::CreateArc(double x1, double y1, double x2, double y2, double angle)
{
	ID id;
	Array<double> params;
	params.PushBack(x1);
	params.PushBack(y1);
	params.PushBack(x2);
	params.PushBack(y2);
	params.PushBack(angle);
	model->createObject(arc, params, id);
	return id;
}

Presenter::Presenter(IView* view)
{
	this->view = view;
	model = new Model();
	controller = new Controller(this);

	controller->AddButton(single_selecting, Vector2(10, 300), Vector2(30, 280));
	controller->AddButton(segment_creating, Vector2(50, 300), Vector2(70, 280));
	controller->AddButton(merging_points, Vector2(90, 300), Vector2(110, 280));
	controller->AddButton(segments_equal, Vector2(130, 300), Vector2(150, 280));
}

Presenter::Presenter()
{
	model = new Model();
	controller = new Controller(this);
}

bool Presenter::CreateRequirmentDistBetPoints(ID point1, ID point2, double d)
{
	Array<double> params;
	Array<ID> components;

	components.PushBack(point1);
	components.PushBack(point2);
	params.PushBack(d);

	if (model->createRequirement(distBetPoints, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentPointsOnTheOneHand(ID segment, ID point1, ID point2)
{
	Array<double> params;//empty
	Array<ID> components;

	components.PushBack(segment);
	components.PushBack(point1);
	components.PushBack(point2);

	if (model->createRequirement(pointsOnTheOneHand, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentDistanceBetweenPointSegment(ID segment, ID point, double d)
{
	Array<double> params;
	Array<ID> components;

	components.PushBack(segment);
	components.PushBack(point);
	params.PushBack(d);

	if (model->createRequirement(distBetPointSeg, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentAngleBetweenSegments(ID segment1, ID segment2, double a)
{
	Array<double> params;
	Array<ID> components;

	components.PushBack(segment1);
	components.PushBack(segment2);
	params.PushBack(a);

	if (model->createRequirement(angleBetSeg, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentDistanceBetweenPointArc(ID arc, ID point, double d)
{
	Array<double> params;
	Array<ID> components;

	components.PushBack(arc);
	components.PushBack(point);
	params.PushBack(d);

	if (model->createRequirement(distBetPointArc, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentPointInArc(ID arc, ID point)
{
	Array<double> params;//empty
	Array<ID> components;

	components.PushBack(arc);
	components.PushBack(point);


	if (model->createRequirement(pointInArc, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentTriangle(ID segment1, ID segment2, ID segment3) {
	Array<double> params;//empty
	Array<ID> components;

	components.PushBack(segment1);
	components.PushBack(segment2);
	components.PushBack(segment3);


	if (model->createRequirement(triangle, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentCorrectTriangle(ID segment1, ID segment2, ID segment3, double size) {
	Array<double> params;
	Array<ID> components;

	components.PushBack(segment1);
	components.PushBack(segment2);
	components.PushBack(segment3);
	params.PushBack(size);

	if (model->createRequirement(correctTriangle, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentNsAngle(Array<ID>& components) {
	Array<double> params;

	if (model->createRequirement(nsAngle, components, params)) {
		return true;
	}
	else {
		return false;
	}
}
bool Presenter::CreateRequirmentCorrectNsAngle(Array<ID>& components, double size) {
	Array<double> params;

	params.PushBack(size);

	if (model->createRequirement(correctNsAngle, components, params)) {
		return true;
	}
	else {
		return false;
	}
}



void Presenter::Optimize() {
	model->OptimizeAllRequirements();
	DrawScene();
}
//void Presenter::PrintSystemRequirement() {
//	model->PrintSystemRequirement();
//}
bool Presenter::getObjParam(const ID& id, Array<double>& array) {
	if (model->getObjParam(id, array)) {
		return true;
	}
	else {
		return false;
	}
}

void Presenter::DrawPoint(double x, double y)
{
	CreatePoint(x, y);
	//DrawScene();
}

void Presenter::DrawSegment(double x1, double y1, double x2, double y2)
{
	CreateSegment(x1, y1, x2, y2);
	DrawScene();
}
void Presenter::DrawTriangle(
	double seg1x1, double seg1y1, double seg1x2, double seg1y2,
	double seg2x1, double seg2y1, double seg2x2, double seg2y2,
	double seg3x1, double seg3y1, double seg3x2, double seg3y2
)
{
	ID segment1 = CreateSegment(seg1x1, seg1y1, seg1x2, seg1y2);
	ID segment2 = CreateSegment(seg2x1, seg2y1, seg2x2, seg2y2);
	ID segment3 = CreateSegment(seg3x1, seg3y1, seg3x2, seg3y2);

	Array<ID> points1;
	Array<ID> points2;
	Array<ID> points3;

	model->GetSegmentPoints(segment1, points1);
	model->GetSegmentPoints(segment2, points2);
	model->GetSegmentPoints(segment3, points3);

	CreateRequirmentDistBetPoints(points1[1], points3[0], 0.0);
	CreateRequirmentDistBetPoints(points1[0], points2[1], 0.0);
	CreateRequirmentDistBetPoints(points3[1], points2[0], 0.0);

	CreateRequirmentDistBetPoints(points1[1], points1[0], 35.0);
	CreateRequirmentDistBetPoints(points2[0], points2[1], 35.0);
	CreateRequirmentDistBetPoints(points3[1], points3[0], 35.0);

	model->Optimize1();
	//Draw();
}

bool Presenter::GetClickedObjectID(double x, double y, ID& obj_id) {
	return model->getNearest(x, y, obj_id);
}

bool Presenter::GetObjType(const ID& id, type_id& type) {
	return model->getObjType(id, type);
}

void Presenter::ClickSceneEvent(double x, double y) {
	controller->ClickAt(x, y);
	DrawScene();
}
void Presenter::KeyPressedEvent(char c) {
	if (c == ' ') {
		controller->SetState(segment_creating);
	}
	if (c == 'd') {
		controller->SetState(merging_points);
	}
	DrawScene();
}

bool Presenter::CreateRequirmentEqualSegmentLen(ID seg1, ID seg2) {
	type_id type1;
	type_id type2;
	if (model->getObjType(seg1, type1) && model->getObjType(seg2, type2) &&
		type1 == segment && type2 == segment) {
		Array<ID> segments;
		Array<double> params(1);

		segments.PushBack(seg1);
		segments.PushBack(seg2);

		return model->createRequirement(equalSegmentLen, segments, params);
	}
	else {
		return false;
	}
}



//void Prese