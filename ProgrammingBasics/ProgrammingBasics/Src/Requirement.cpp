#include <Requirement.h>

#pragma region Requirement
Requirement::Requirement(object_type _type, const Array<double>& _params, const Array<ID>& _children) :
	Object(_type, _params, _children), args(0)
{
	primCtrl = PrimController::GetInstance();
}

Array<double*> Requirement::GetArgs() const {
	return args;
}

Array<double> Requirement::Gradient() {
	Array<double> grad(args.GetSize());
	double err = error();
	for (int i = 0; i < args.GetSize(); ++i) {
		double test = *args[i];
		(*args[i]) += DELTA_X;
		double delta_error_right = error();
		(*args[i]) -= DELTA_X;
		//(*arguments[i]) -= 2 * DELTA_X;
		//double delta_error_left = error();

		test = (delta_error_right - err) / (DELTA_X);
		//test = (delta_error_right - delta_error_left) / (DELTA_X * 2);
		grad[i] = test;
	}
	return grad;
}
#pragma endregion

#pragma region DistBetPointsReq
DistBetPointsReq::DistBetPointsReq(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_distBetPoints, _params, _objects)
{
	for (int i = 0; i < _objects.GetSize(); ++i) {
		args += primCtrl->GetPrimitiveDoubleParamsAsPointers(_objects[i]);
	}
}

double DistBetPointsReq::error() {
	Vector2 vectorAB(*(args[2]) - *(args[0]), *(args[3]) - *(args[1]));
	double modAB_inSquare = Vector2::Dot(vectorAB, vectorAB);
	return modAB_inSquare - params[0] * (2 * sqrt(modAB_inSquare) - params[0]);
}
#pragma endregion

#pragma region EqualSegment
EqualSegmentLenReq::EqualSegmentLenReq(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_equalSegmentLen, _params, _objects)
{
	Array<ID> allPoints = primCtrl->GetChildren(_objects[0]) +
		primCtrl->GetChildren(_objects[1]);

	for (int i = 0; i < allPoints.GetSize(); ++i) {
		args += primCtrl->GetPrimitiveDoubleParamsAsPointers(allPoints[i]);
	}
}

double EqualSegmentLenReq::error() {
	Vector2 vec1(*(args[3]) - *(args[1]), *(args[2]) - *(args[0]));
	Vector2 vec2(*(args[7]) - *(args[5]), *(args[6]) - *(args[4]));

	double divergence = vec2.GetLength() - vec1.GetLength();
	return divergence * divergence;
}
#pragma endregion

#pragma region PointPosReq
PointPosReq::PointPosReq(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_pointPosReq, _params, _objects) {

	for (int i = 0; i < _objects.GetSize(); ++i) {
		args += primCtrl->GetPrimitiveDoubleParamsAsPointers(_objects[i]);
	}
}

double PointPosReq::error() {
	Vector2 vector(*args[0] - params[0], *args[1] - params[1]);
	return Vector2::Dot(vector, vector);
}
#pragma endregion

#pragma region PointsOnTheOneHand
PointsOnTheOneHand::PointsOnTheOneHand(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_pointsOnTheOneHand, params, _objects)
{
	Array<ID> objs = primCtrl->GetChildren(_objects[0]) +
		_objects[1] + _objects[2];

	for (int i = 0; i < objs.GetSize(); ++i) {
		args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(objs[i]);
	}
}

double PointsOnTheOneHand::error() {
	Vector2 pointPos1 = Vector2(*args[4], *args[5]);
	Vector2 pointPos2 = Vector2(*args[6], *args[7]);

	double Fx1 = /*segment->Inequality(pointPos1)*/0; // FIX
	double Fx2 =/* segment->Inequality(pointPos2)*/0; // FIX
	if ((Fx1 > 0 && Fx2 < 0) || (Fx1 < 0 && Fx2 > 0)) {
		Fx1 = abs(Fx1);
		Fx2 = abs(Fx2);

		if (Fx1 > Fx2) {
			double distance = /*segment->GetDist(pointPos2)*/0;
			return distance * distance;
		}
		else {
			double distance = /*segment->GetDist(pointPos1)*/0;
			return distance * distance;
		}
	}
	return 0;
}
#pragma endregion

#pragma region DistanceBetweenPointSegment
// _objects = <segment, point>
DistanceBetweenPointSegment::DistanceBetweenPointSegment(const Array<ID>& _objects,
	const Array<double>& _params) :
	Requirement(ot_distBetPointSeg, _params, _objects)
{
	Array<ID> objs = primCtrl->GetChildren(_objects[0]) + _objects[1];
	for (int i = 0; i < objs.GetSize(); ++i) {
		args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(objs[i]);
	}
}

double DistanceBetweenPointSegment::error() {
	Vector2 point(*args[4], *args[5]);
	double distance = /*segment->GetDist(point)*/ -params[0]; //FIX
	return distance * distance;
}

Array<double> DistanceBetweenPointSegment::gradient() {
	return Array<double>();
}
#pragma endregion

#pragma region AngleBetweenSegments
AngleBetweenSegments::AngleBetweenSegments(const Array<ID>& _objects,
	const Array<double>& _params) :
	Requirement(ot_distBetPointSeg, _params, _objects)
{



}

double AngleBetweenSegments::error() {
	if (abs(params[0] - angle) - DELTA_X > 0) {
		ChangeParams();
	}
	Vector2 vec1(*args[2] - *args[0], *args[3] - *args[1]);
	Vector2 vec2(*args[6] - *args[4], *args[7] - *args[5]);

	double length1 = vec1.GetLength();
	double length2 = vec2.GetLength();

	// smaller side triangle:
	Vector2 vec3 = vec1 - vec2;
	if (Vector2::Dot(vec3, vec3) > length1 * length1 + length2 * length2 + DELTA_X) {
		vec3 = (vec1 * -1) - vec2;
	}
	//
	double length3 = sqrt(length1 * length1 + length2 * length2 - 2 * params[0] * length2* length1);

	double different = length3 - vec3.GetLength();
	return different * different;
}

void AngleBetweenSegments::ChangeParams() {
	angle = params[0];
	if (angle  == 90) {
		cosinus = 0;
		sinus = 1;
	}
	else if (angle == 0) {
		cosinus = 1;
		sinus = 0;
	}
	else {
		cosinus = abs(cos((angle / 180) * PI));
		sinus = sin((angle / 180) * PI);
	}
}
#pragma endregion

#pragma region DistanceBetweenPointArc
DistanceBetweenPointArc::DistanceBetweenPointArc(Arc* _arc, Point* _point, double _distance) :
	arc(_arc),
	point(_point),
	Requirement(IDGenerator::getInstance()->generateID(), ot_distBetPointArc)
{
	args = Array<double*>(7);
	params = Array<double>(1);

	args[0] = &_arc->point1->pos.x;
	args[1] = &_arc->point1->pos.y;
	args[2] = &_arc->point2->pos.x;
	args[3] = &_arc->point2->pos.y;
	args[4] = &_arc->angle;
	args[5] = &_point->pos.x;
	args[6] = &_point->pos.y;

	params[0] = _distance;
}

double DistanceBetweenPointArc::error() {
	Vector2 vector(point->pos - arc->GetCenter());
	double modVector_inSquare = Vector2::Dot(vector, vector);
	return modVector_inSquare - params[0] * (2 * sqrt(modVector_inSquare) - params[0]);
}
#pragma endregion

#pragma region SegmentTouchCircle
SegmentTouchCircle::SegmentTouchCircle(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_segmentTouchCircle, _params, _objects)
{
	Array<ID> objs =
		primCtrl->GetChildren(_objects[0]) +
		primCtrl->GetChildren(_objects[1]) +
		_objects[1];

	for (int i = 0; i < objs.GetSize(); ++i) {
		args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(objs[i]);
	}
}

double SegmentTouchCircle::error() {
	return 0.0;
}
#pragma endregion

#pragma region PointInArc
PointInArc::PointInArc(Arc* _arc, Point* _point) :
	arc(_arc),
	point(_point),
	Requirement(IDGenerator::getInstance()->generateID(), ot_pointInArc)
{
	args[0] = &_arc->point1->pos.x;
	args[1] = &_arc->point1->pos.y;
	args[2] = &_arc->point2->pos.x;
	args[3] = &_arc->point2->pos.y;
	args[4] = &_arc->angle;
	args[5] = &_point->pos.x;
	args[6] = &_point->pos.y;
}

// return distance to arc and angle
double PointInArc::error() {
	Vector2 center = arc->GetCenter();
	Vector2 vec1 = arc->GetPointPos1() - center;
	Vector2 vecPoint = point->GetPos() - center;
	double angle = Vector2::Angle(vec1, vecPoint);
	double angleArc = arc->GetAngle();
	if (angle <= angleArc) {
		return 0;
	}
	if (angle <= PI + angleArc / 2) {
		if (angle < angleArc + PI / 2) {
			return point->GetDist(center) * sin(angle - angleArc);
		}
		else {
			return point->GetDist(center) + angle;
		}
	}
	else {
		if (angle < PI / 2) {
			return point->GetDist(center) * sin(angle);
		}
		else {
			return point->GetDist(center);
		}
	}
}
#pragma endregion