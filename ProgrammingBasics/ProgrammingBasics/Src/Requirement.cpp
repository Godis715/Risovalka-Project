#include <Requirement.h>

template Array<double>;
template Array<double*>;

Requirement::Requirement(object_type _type, const Array<double*>& _args) :
	Object(_type),
	args(_args)
{

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
	default: {
		throw std::exception("Couldn't create requirement. Invalid requirement type");
	}
	}

	if (argNum != args.GetSize()) {
		throw std::exception("Couldn't create requirement. Invalid number of arguments");
	}

	params = Array<double>(paramNum);
}

Array<double*> Requirement::GetArgs() {
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

void Requirement::Change(const double) {}