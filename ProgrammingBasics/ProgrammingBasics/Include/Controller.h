#pragma once

#include "Presenter.h"

enum state_id { segment_creating, single_selecting, poly_selecting, merging_points};

class Controller {
private:
	Presenter* presenter;

	state_id state;
	state_id defaultState;

	Array<ID> selectedObjects;
	Array<Vector2> clickedPoints;

	void refresh();
public:

	Controller(Presenter*);

	void SetState(state_id);
	void ClickAt(double, double);
};
