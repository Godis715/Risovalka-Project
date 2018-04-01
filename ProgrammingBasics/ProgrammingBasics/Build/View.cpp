#include "View.h"

View::View()
{
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hDC, hPen);
	GetClientRect(hWnd, &screen);

	DWORD Mode;
	GetConsoleMode(hWnd, &Mode);
	SetConsoleMode(hWnd, Mode | ENABLE_MOUSE_INPUT);
}

void View::Run() {

	Vector2 point1;
	Vector2 point2;
	bool isFirstPressed = false;

	while (true) {
		WaitForSingleObject(hWnd, INFINITE);

		INPUT_RECORD InRec;
		DWORD NumEvents;
		BOOL b = ReadConsoleInputW(hWnd, &InRec, 1, &NumEvents);

		if (NumEvents != 0 && InRec.EventType == MOUSE_EVENT) {

			double mouseX = InRec.Event.MouseEvent.dwMousePosition.X;
			double mouseY = InRec.Event.MouseEvent.dwMousePosition.Y;

			if (!isFirstPressed) {
				point1.x = mouseX;
				point1.y = mouseY;
				isFirstPressed = true;
			}
			else {
				point2.x = mouseX;
				point2.y = mouseY;
				isFirstPressed = false;
				presenter->DrawSegment(point1.x, point1.y, point2.x, point2.y);
			}
		}
	}

}

void View::DrawArc(Vector2 point1, Vector2 point2) {
	
}

void View::DrawLine(Vector2 point1, Vector2 point2) {
	MoveToEx(hDC, (int)point1.x, screen.top - (int)point1.y, NULL);
	LineTo(hDC, (int)point2.x, screen.top - (int)point2.y);
}

void View::DrawPoint(Vector2 point) {
	
}