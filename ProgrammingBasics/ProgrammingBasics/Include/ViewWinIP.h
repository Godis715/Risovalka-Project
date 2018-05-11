#ifndef __VIEW_WINIP
#define __VIEW_WINIP

#include "Presenter.h"
#include "IView.h"
#include <windows.h>

class ViewWinIP : public IView
{
private:
	Presenter* presenter;
	HWND hWnd;

	HDC hDC;
	HPEN hPen;
	RECT screen;
public:
	ViewWinIP();
	void DrawLine(const Vector2&, const Vector2&);
	void DrawArc(const Vector2&, const Vector2&);
	void DrawPoint(const Vector2&);
	void SetColor(color);

	int Run();
	void Clear();
};

#endif

