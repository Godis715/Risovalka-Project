#include <Requirement.h>

template Array<double>;
template Array<double*>;

/*template <typename T> Parameters<T>::Parameters() { }
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

template <typename T> Parameters<T>::Parameters(int _size, T val) {
	params = new T[_size];
	num = _size;
	for (int i = 0; i < _size; ++i) {
		params[i] = val;
	}
}

template <typename T> int Parameters<T>::GetSize() const {
	return num;
}
*/

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