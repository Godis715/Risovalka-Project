#include <Requirement.h>

template Array<double>;
template Array<double*>;

Array<double*> IRequirement::GetParams() {
	return params;
}

Array<double> IRequirement::gradient() {
	Array<double> grad(params_num);
	double err = error();
	for (int i = 0; i < params_num; ++i) {

		(*params[i]) += DELTA_X;
		double delta_error_right = error();

		(*params[i]) -= 2 * DELTA_X;
		double delta_error_left = error();

		(*params[i]) += DELTA_X;

		grad[i] = (delta_error_right - delta_error_left) / (DELTA_X * 2);
	}
	return grad;
}

bool IRequirement::Contains(ID id) {
	for (int i = 0; i < primitives.GetSize(); ++i) {
		if (primitives[i]->GetID() == id) {
			return true;
		}
	}
	return false;
}

void IRequirement::GetPrimitivesID(Array<ID>& IDArray) {
	for (int i = 0; i < primitives.GetSize(); ++i) {
		IDArray.PushBack(primitives[i]->GetID());
	}
}