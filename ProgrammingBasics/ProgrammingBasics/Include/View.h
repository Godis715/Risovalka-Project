#pragma once

#include "Presenter.h"
#include "IView.h"
#include <windows.h>


class View : public IView
{
private:
	Presenter* presenter;

public:
	//void DrawLine(Vector2 point1, Vector2 point2);
	/*View() : presenter(new Presenter(this))
	{

	}*/
};

