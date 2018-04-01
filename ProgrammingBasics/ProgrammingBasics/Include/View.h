#pragma once

#include "Presenter.h"
#include "IView.h"
#include <windows.h>


class View : public IView
{
private:
	Presenter* presenter;

public:
	View();
	void DrawLine(Vector2 point1, Vector2 point2);
	void DrawArc(Vector2 point1, Vector2 point2);
	void DrawPoint(Vector2 point);

	void Run();
};

