#include "Optimizer.h"

#define OPTIM_GRAD_EPS 1e-3
#define OPTIM_EPS 1e-2


Optimizer::Optimizer() {
	reqCtrl = ReqController::GetInstance();
}

void Optimizer::OptimizeRequirements(const Array<ID>& requirments) {
	// get parameters number
	Array<double*> params;
	for (int i = 0; i < requirments.GetSize(); ++i) {
		params = params + reqCtrl->GetReqArgsAsPointers(requirments[i]);
	}

	// anti gradient
	Array<double> aGradient(params.GetSize(), 0.0);

	//filling anti gradient
	double err = reqCtrl->GetReqError(requirments);
	int optimization_iter = 0;
	while (err > OPTIM_EPS) {

		int match_array_iterator = 0;

		for (int i = 0; i < requirments.GetSize(); ++i) {

			Array<double> currentGradient = reqCtrl->GetGradient(requirments[i]);

			for (int j = 0; j < currentGradient.GetSize(); ++j) {

				aGradient[match_array_iterator] -= 
					currentGradient[j] / requirments.GetSize();

				++match_array_iterator;
			}
		}

		OptimizeByGradient(requirments, params, aGradient);
		aGradient.FillDefault(0.0);
		err = reqCtrl->GetReqError(requirments);

		optimization_iter++;
		// temp
		if (optimization_iter >= 200) {
			break;
		}
	}
	for (int i = 0; i < requirments.GetSize(); ++i) {
		reqCtrl->ApplyChanges(requirments[i]);
	}
}

void Optimizer::OptimizeByGradient
	(const Array<ID>& reqs,
	const Array<double*> args,
	const Array<double>& agrad) 
{

	const double gold_section = 1.6180339887498;
	int reqSize = reqs.GetSize();

	double error = reqCtrl->GetReqError(reqs);

	double left = 0.0;
	double right = 0.1;

	double leftValue = ErrorByAlpha(reqs, args, agrad, left);
	double rightValue = ErrorByAlpha(reqs, args, agrad, right);

	double x1 = right - (right - left) / gold_section;
	double x2 = left + (right - left) / gold_section;

	double x1_Value = ErrorByAlpha(reqs, args, agrad, x1);
	double x2_Value = ErrorByAlpha(reqs, args, agrad, x2);

	while (abs(leftValue - rightValue) > OPTIM_GRAD_EPS * error) {

		if (x1_Value > x2_Value) {
			left = x1;
			leftValue = x1_Value;
			x1 = x2;
			x1_Value = x2_Value;
			x2 = left + (right - left) / gold_section;
			x2_Value = ErrorByAlpha(reqs, args, agrad, x2);
		}
		else {
			right = x2;
			rightValue = x2_Value;
			x2 = x1;
			x1 = right - (right - left) / gold_section;
			x2_Value = x1_Value;
			x1_Value = ErrorByAlpha(reqs, args, agrad, x1);
		}
	}

	double alpha = (leftValue < rightValue) ? left : right;

	for (int i = 0; i < args.GetSize(); ++i) {
		(*args[i]) += agrad[i] * alpha;
	}
}

double Optimizer::ErrorByAlpha
	(const Array<ID>& reqs,
	const Array<double*> args,
	const Array<double>& agrad,
	double alpha)
{
	for (int i = 0; i < args.GetSize(); ++i) {
		double delta = agrad[i];
		*(args[i]) += delta * alpha;
	}
	double error = reqCtrl->GetReqError(reqs);
	for (int i = 0; i < args.GetSize(); ++i) {
		*(args[i]) -= agrad[i] * alpha;
	}
	return error;
}
