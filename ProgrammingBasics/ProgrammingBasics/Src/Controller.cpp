#include "Controller.h"

Controller::Controller(Presenter* _presenter) {
	presenter = _presenter;
	state = single_selecting;
	defaultState = single_selecting;
}

void Controller::ClickAt(double x, double y) {

	for (int i = 0; i < buttons.getSize(); ++i) {
		if (buttons[i].IsClicked(Vector2(x, y))) {
			SetState(buttons[i].state);
			return;
		}
	}

	ID obj_id;
	if (presenter->GetClickedObjectID(x, y, obj_id)) {
		switch (state) {
		case single_selecting: {
			if (!selectedObjects.isEmpty()) {
				selectedObjects.clear();
			}
			selectedObjects.pushBack(obj_id);
			break;
		}
		case poly_selecting: {
			selectedObjects.pushBack(obj_id);
			break;
		}
		case merging_points: {
			type_id type;
			if (presenter->GetObjType(obj_id, type) && type == point) {
				selectedObjects.pushBack(obj_id);
				refresh();
			}
			break;
		}
		case segment_creating: {
			selectedObjects.pushBack(obj_id);
			refresh();
		}
		}

	}
	else {
		switch (state) {
		case segment_creating: {
			clickedPoints.pushBack(Vector2(x, y));
			refresh();
			break;
		}
		default:
			state = single_selecting;
			clickedPoints.clear();
			selectedObjects.clear();
			break;
		}
	}

}

void Controller::SetState(state_id _state) {
	state = _state;
	refresh();
}

void Controller::refresh() {
	switch (state) {
	case merging_points: {
		if (selectedObjects.getSize() > 2) {
			selectedObjects.clear();
			return;
		}
		if (selectedObjects.getSize() == 2) {

			presenter->CreateRequirmentDistBetPoints(selectedObjects[0], selectedObjects[1], 0.0);
			presenter->Optimize();
			selectedObjects.clear();
			state = single_selecting;
			return;
		}
		break;
	}
	case segment_creating: {
		selectedObjects.clear();
		if (clickedPoints.getSize() > 2) {
			clickedPoints.clear();
			return;
		}
		if (clickedPoints.getSize() == 2) {
			presenter->CreateSegment(clickedPoints[0].x, clickedPoints[0].y,
				clickedPoints[1].x, clickedPoints[1].y);
			clickedPoints.clear();
			state = single_selecting;
		}
	}
	}
}

void Controller::AddButton(state_id _state, Vector2 _pos1, Vector2 _pos2) {
	buttons.pushBack(Button(_state, _pos1, _pos2));
}

Button::Button(state_id _state, Vector2 lu, Vector2 rd) {
	state = _state;
	leftUp = lu;
	rightDown = rd;
}
bool  Button::IsClicked(Vector2 pos) {
	return pos.y >= rightDown.y &&
		pos.y <= leftUp.y &&
		pos.x >= leftUp.x &&
		pos.x <= rightDown.x;
}