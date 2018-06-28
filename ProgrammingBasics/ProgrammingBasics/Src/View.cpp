#include "View.h"
View::View()
{
	presenter = new Presenter(this);
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hDC, hPen);
	GetClientRect(hWnd, &screen);

	DWORD Mode;
	GetConsoleMode(hWnd, &Mode);
	SetConsoleMode(hWnd, Mode | ENABLE_MOUSE_INPUT);
}

void View::Clear() {
	HBRUSH brush = CreateSolidBrush(0);
	FillRect(hDC, &screen, brush);
}

void View::Run() {

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	while (true) {
		WaitForSingleObject(hStdin, INFINITE);

		INPUT_RECORD InRec;
		DWORD NumEvents;
		BOOL b = ReadConsoleInputW(hStdin, &InRec, 3, &NumEvents);
		POINT pos;
		if (NumEvents != 0 && InRec.EventType == MOUSE_EVENT && InRec.Event.MouseEvent.dwButtonState == RI_MOUSE_BUTTON_1_DOWN) {
			GetCursorPos(&pos);
			ScreenToClient(hWnd, &pos);
			if (pos.x <= 20 && pos.y <= 20) {
				presenter->KeyPressedEvent(' ');
				continue;
			}
			if (pos.x <= 20) {
				presenter->KeyPressedEvent('d');
				continue;
			}
			presenter->ClickSceneEvent(pos.x, pos.y);

		}
	}
}


void View::DrawArc(const Vector2& point1, const Vector2& point2) {
	
}

void View::DrawLine(const Vector2& point1, const Vector2& point2) {
	MoveToEx(hDC, (int)point1.x, (int)point1.y, NULL);
	LineTo(hDC,(int)point2.x, (int)point2.y);
}

void View::DrawPoint(const Vector2& point) {
	const double size = 3.0;
	MoveToEx(hDC, (int)point.x - size, (int)point.y - size, NULL);
	LineTo(hDC, (int)point.x + size, (int)point.y + size);

	MoveToEx(hDC, (int)point.x + size, (int)point.y - size, NULL);
	LineTo(hDC, (int)point.x - size, (int)point.y + size);
}

void View::SetColor(color col) {
	
	COLORREF pen_color;
	if (col == red) {
		pen_color = RGB(255, 0, 0);
	}
	if (col == white) {
		pen_color = RGB(255, 255, 255);
	}

	hPen = CreatePen(PS_SOLID, 1, pen_color);

	SelectObject(hDC, hPen);
}