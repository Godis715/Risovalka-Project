#ifndef __OPTIMIZER
#define __OPTIMIZER

#include "DataController.h"

class Optimizer {
private:
	ReqController* reqCtrl;

	void OptimizeByGradient(const Array<ID>&, const Array<double*>, const Array<double>&);
	double ErrorByAlpha(const Array<ID>&, const Array<double*>, const Array<double>&, double);
public:
	Optimizer();
	void OptimizeRequirements(const Array<ID>&);
};

#endif