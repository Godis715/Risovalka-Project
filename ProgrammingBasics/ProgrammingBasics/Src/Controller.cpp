#include "Controller.h"

Controller::Controller(Presenter* _presenter) {
	presenter = _presenter;
	state = single_selecting;
	defaultState = single_selecting;
}

void Controller::ClickAt(double x, double y) {
	SetState(segment_creating);
	for (int i = 0; i < buttons.GetSize(); ++i) {
		if (buttons[i].IsClicked(Vector2(x, y))) {
			SetState(buttons[i].state);
			return;
		}
	}

	ID obj_id;
	if (presenter->GetClickedObjectID(x, y, obj_id)) {
		switch (state) {
		case single_selecting: {
			if (!selectedObjects.IsEmpty()) {
				selectedObjects.Clear();
			}
			selectedObjects.PushBack(obj_id);
			break;
		}
		case poly_selecting: {
			selectedObjects.PushBack(obj_id);
			break;
		}
		case merging_points: {
			type_id type;
			if (presenter->GetObjType(obj_id, type) && type == point) {
				selectedObjects.PushBack(obj_id);
				refresh();
			}
			break;
		}
		case segment_creating: {
			selectedObjects.PushBack(obj_id);
			refresh();
			break;
		}
		case segments_equal: {
			type_id type;
			if (presenter->GetObjType(obj_id, type) && type == segment) {
				selectedObjects.PushBack(obj_id);
				refresh();
			}
		}
		}

	}
	else {
		switch (state) {
		case segment_creating: {
			clickedPoints.PushBack(Vector2(x, y));
			refresh();
			break;
		}
		default:
			state = single_selecting;
			clickedPoints.Clear();
			selectedObjects.Clear();
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
		if (selectedObjects.GetSize() > 2) {
			selectedObjects.Clear();
			return;
		}
		if (selectedObjects.GetSize() == 2) {

			presenter->CreateRequirmentDistBetPoints(selectedObjects[0], selectedObjects[1], 0.0);
			presenter->Optimize();
			selectedObjects.Clear();
			state = single_selecting;
			return;
		}
		break;
	}
	case segment_creating: {
		selectedObjects.Clear();
		if (clickedPoints.GetSize() > 2) {
			clickedPoints.Clear();
			return;
		}
		if (clickedPoints.GetSize() == 2) {
			presenter->CreateSegment(clickedPoints[0].x, clickedPoints[0].y,
				clickedPoints[1].x, clickedPoints[1].y);
			clickedPoints.Clear();
			state = single_selecting;
		}
		break;
	}
	case segments_equal: {
		if (selectedObjects.GetSize() == 2) {
			if (presenter->CreateRequirmentEqualSegmentLen(selectedObjects[0], selectedObjects[1])) {
				state = single_selecting;
				presenter->Optimize();
			}
			selectedObjects.Clear();
		}
		if (selectedObjects.GetSize() > 2) {
			selectedObjects.Clear();
		}
		break;
	}
	}
}

void Controller::AddButton(state_id _state, Vector2 _pos1, Vector2 _pos2) {
	buttons.PushBack(Button(_state, _pos1, _pos2));
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