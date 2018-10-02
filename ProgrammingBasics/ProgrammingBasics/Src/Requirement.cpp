#include <Requirement.h>

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

DistBetPointsReq::DistBetPointsReq(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_distBetPoints, _params, _objects)
{
	for (int i = 0; i < _objects.GetSize(); ++i) {
		args = args + primCtrl->GetPrimitiveDoubleParamsAsPointers(_objects[i]);
	}
}

double DistBetPointsReq::error() {
	Vector2 vectorAB(*(args[2]) - *(args[0]), *(args[3]) - *(args[1]));
	double modAB_inSquare = Vector2::Dot(vectorAB, vectorAB);
	return modAB_inSquare - params[0] * (2 * sqrt(modAB_inSquare) - params[0]);
}