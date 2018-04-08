#pragma once

#include "Presenter.h"
#include "IView.h"
#include <windows.h>


class View : public IView
{
private:
	Presenter* presenter;
	HWND hWnd;
	HDC hDC;
	HPEN hPen;
	RECT screen;
public:
	View();
	void DrawLine(Vector2, Vector2);
	void DrawArc(Vector2, Vector2);
	void DrawPoint(Vector2);
	void SetColor(color);

	void Run();
	void Clear();
};

