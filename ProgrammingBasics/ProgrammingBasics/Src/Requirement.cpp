#include <Requirement.h>

//template Array<double>;
//template Array<double*>;

Array<double*> Requirement::GetArguments() {
	return arguments;
}

Array<double> Requirement::GetParams()
{
	return params;
}

Array<double> Requirement::Gradient() {
	Array<double> grad(arguments.GetSize());
	double err = error();
	for (int i = 0; i < arguments.GetSize(); ++i) {
		double test = *arguments[i];
		(*arguments[i]) += DELTA_X;
		double delta_error_right = error();
		(*arguments[i]) -= DELTA_X;
		//(*arguments[i]) -= 2 * DELTA_X;
		//double delta_error_left = error();

		test = (delta_error_right - err) / (DELTA_X);
		//test = (delta_error_right - delta_error_left) / (DELTA_X * 2);
		grad[i] = test;
	}
	return grad;
}

ID Requirement::GetID() const {
	return id;
}

object_type Requirement::GetType() const {
	return type;
}

void Requirement::Change(const double newPar)
{
	//params[0] = newPar;
}
