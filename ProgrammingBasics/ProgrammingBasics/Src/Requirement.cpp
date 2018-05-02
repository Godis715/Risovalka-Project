#include <Requirement.h>

template Array<double>;
template Array<double*>;

Array<double*> Requirement::GetParams() {
	return params;
}

Array<double> Requirement::gradient() {
	Array<double> grad(params.GetSize());
	double err = error();
	for (int i = 0; i < params.GetSize(); ++i) {

		(*params[i]) += DELTA_X;
		double delta_error_right = error();

		(*params[i]) -= 2 * DELTA_X;
		double delta_error_left = error();

		(*params[i]) += DELTA_X;

		grad[i] = (delta_error_right - delta_error_left) / (DELTA_X * 2);
	}
	return grad;
}

ID Requirement::GetID() const {
	return id;
}

Requirement_id Requirement::GetType() const {
	return type;
}