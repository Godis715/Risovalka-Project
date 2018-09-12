#include <Requirement.h>


Requirement::Requirement(object_type _type, const Array<double>& _params) :
	Object(_type),
	params(_params)
{
	primCtrl = PrimController::GetInstance();

	int argNum;
	int paramNum;

	switch (type) {
	case ot_distBetPoints: {
		argNum = 4;
		paramNum = 1;
		break;
	}
	case ot_equalSegmentLen: {
		argNum = 8;
		paramNum = 0;
		break;
	}
	case ot_connection: {
		argNum = 0;
		paramNum = 0;
		break;
	}
	case ot_pointPosReq: {
		argNum = 2;
		paramNum = 2;
		break;
	}
	case ot_pointsOnTheOneHand: {
		argNum = 8;
		paramNum = 0;
		break;
	}
	case ot_distBetPointSeg: {
		argNum = 6;
		paramNum = 1;
		break;
	}
	case ot_angleBetSeg: {
		argNum = 8;
		paramNum = 1;
		break;
	}
	case ot_distBetPointArc: {
		argNum = 7;
		paramNum = 1;
		break;
	}
	case ot_pointInArc: {
		argNum = 7;
		paramNum = 0;
		break;
	}
	case ot_segmentTouchCircle: {
		argNum = 7;
		paramNum = 0;
		break;
	}
	default: {
		throw std::exception("Couldn't create requirement. Invalid requirement type");
	}
	}

	
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

void Requirement::Change(const double) { }

DistBetPointsReq::DistBetPointsReq(const Array<ID>& _objects, const Array<double>& _params) :
	Requirement(ot_distBetPoints, _params)
{
	args = primCtrl->GetPrimitiveParamsAsPointers(_objects, 4);
}

double DistBetPointsReq::error() {
	Vector2 vectorAB(*(args[2]) - *(args[0]), *(args[3]) - *(args[1]));
	double modAB_inSquare = Vector2::Dot(vectorAB, vectorAB);
	return modAB_inSquare - params[0] * (2 * sqrt(modAB_inSquare) - params[0]);
}