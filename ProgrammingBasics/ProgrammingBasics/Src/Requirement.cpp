#include <Requirement.h>

template Parameters<double>;
template Parameters<double*>;

template <typename T> Parameters<T>::Parameters() { }
template <typename T> Parameters<T>::Parameters(const Parameters<T>& p) {
	num = p.num;
	params = new T[num];
	for (int i = 0; i < num; ++i) {
		params[i] = p.params[i];
	}
}
template <typename T> Parameters<T>::Parameters(int _size) {
	params = new T[_size];
	num = _size;
}
template <typename T> T& Parameters<T>::operator[](int index) {
	if (index < num) {
		return params[index];
	}
	else {
		throw std::out_of_range("Index out of parameters' number");
	}
}
template <typename T> int Parameters<T>::GetSize() const {
	return num;
}

Parameters<double*> IRequirement::GetParams() {
	return params;
}

Parameters<double> IRequirement::gradient() {
	Parameters<double> grad(params_num);
	double err = error();
	for (int i = 0; i < params_num; ++i) {
		(*params[i]) += EPS;
		double delta_error = error() - err;
		(*params[i]) -= EPS;
		grad[i] = delta_error / EPS;
	}
	return grad;
}