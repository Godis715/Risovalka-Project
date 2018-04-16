#pragma once

#include "Presenter.h"

enum state_id { segment_creating, single_selecting, poly_selecting, merging_points, segments_equal};

class Button {
private:

public:
	Vector2 leftUp;
	Vector2 rightDown;
	Button(state_id, Vector2, Vector2);
	Button() { }
	state_id state;
	bool IsClicked(Vector2);
};

class Controller {
private:
	Presenter* presenter;

	state_id state;
	state_id defaultState;


	void refresh();
public:

	Array<ID> selectedObjects;
	Array<Vector2> clickedPoints;
	Array<Button> buttons;

	Controller(Presenter*);

	void SetState(state_id);
	void ClickAt(double, double);
	void AddButton(state_id, Vector2, Vector2);
};
