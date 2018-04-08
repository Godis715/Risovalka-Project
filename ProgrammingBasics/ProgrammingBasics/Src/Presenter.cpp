#include "Presenter.h"
#include "Controller.h"

void Presenter::DrawScene() {
	view->Clear();
	Array<Model::infoObject> scene;
	if (!model->DischargeInfoObjects(scene)) {
		return;
	}
	for (int i = 0; i < scene.getSize(); ++i) {
		view->SetColor(white);
		if (scene[i].type == segment) {
			view->DrawLine(Vector2(scene[i].params[0], scene[i].params[1]),
				Vector2(scene[i].params[2], scene[i].params[3]));
		}
		if (scene[i].type == point) {
			view->DrawPoint(Vector2(scene[i].params[0], scene[i].params[1]));
		}
	}



	// drawing selected object
}

ID Presenter::CreatePoint(double x, double y) {
	Array<double> params;
	params.pushBack(x);
	params.pushBack(y);

	ID id;
	model->createObject(point, params, id);
	return id;
}
ID Presenter::CreateSegment(double x1, double y1, double x2, double y2) {
	ID id;
	Array<double> params;
	params.pushBack(x1);
	params.pushBack(y1);
	params.pushBack(x2);
	params.pushBack(y2);
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
	params.pushBack(x1);
	params.pushBack(y1);
	params.pushBack(x2);
	params.pushBack(y2);
	params.pushBack(angle);
	model->createObject(arc, params, id);
	return id;
}

Presenter::Presenter(IView* view)
{
	this->view = view;
	model = new Model();
	controller = new Controller(this);
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

	components.pushBack(point1);
	components.pushBack(point2);
	params.pushBack(d);

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

	components.pushBack(segment);
	components.pushBack(point1);
	components.pushBack(point2);

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

	components.pushBack(segment);
	components.pushBack(point);
	params.pushBack(d);

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

	components.pushBack(segment1);
	components.pushBack(segment2);
	params.pushBack(a);

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

	components.pushBack(arc);
	components.pushBack(point);
	params.pushBack(d);

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

	components.pushBack(arc);
	components.pushBack(point);


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

	components.pushBack(segment1);
	components.pushBack(segment2);
	components.pushBack(segment3);


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

	components.pushBack(segment1);
	components.pushBack(segment2);
	components.pushBack(segment3);
	params.pushBack(size);

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

	params.pushBack(size);

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
void Presenter::PrintSystemRequirement() {
	model->PrintSystemRequirement();
}
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
	double dist;
	if (model->getNearest(x, y, obj_id, dist)) {
		if (dist < 5.0) {
			return true;
		}
	}
	return false;
}

bool Presenter::GetObjType(const ID& id, type_id& type) {
	if (model->getObjType(id, type)) {
		return true;
	}
	return false;
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


//void Prese