#include "Presenter.h"
#include "Controller.h"

Presenter::Presenter(IView* view)
{
	this->view = view;
	model = new Model();

	controller->AddButton(single_selecting, Vector2(10, 300), Vector2(30, 280));
	controller->AddButton(segment_creating, Vector2(50, 300), Vector2(70, 280));
	controller->AddButton(merging_points, Vector2(90, 300), Vector2(110, 280));
}

void Presenter::Optimize() {
	model->OptimizeAllRequirements();
	DrawScene();
}

//void Prese