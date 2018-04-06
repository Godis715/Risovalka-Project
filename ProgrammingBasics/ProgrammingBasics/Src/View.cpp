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

	Vector2 point1;
	Vector2 point2;
	bool isFirstPressed = false;
	bool isPointSelected = false;

	ID id_p1;
	ID id_p2;

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
			ID clickedObject;
			if (presenter->GetClickedObjectID(pos.x, pos.y, clickedObject)) {
				if (isPointSelected) {
					id_p2 = clickedObject;
					presenter->CreateRequirmentDistBetPoints(id_p1, id_p2, 0.0);
					presenter->Optimize();
				}
				else {
					id_p1 = clickedObject;
				}
				isPointSelected = !isPointSelected;

			}
			else {
				if (!isFirstPressed) {
					point1.x = pos.x;
					point1.y = pos.y;
					isFirstPressed = true;
				}
				else {
					point2.x = pos.x;
					point2.y = pos.y;
					isFirstPressed = false;
					presenter->DrawSegment(point1.x, point1.y, point2.x, point2.y);
				}
			}
		}

	}
}

void View::DrawArc(Vector2 point1, Vector2 point2) {
	
}

void View::DrawLine(Vector2 point1, Vector2 point2) {

	MoveToEx(hDC, (int)point1.x, (int)point1.y, NULL);
	LineTo(hDC,(int)point2.x, (int)point2.y);
}

void View::DrawPoint(Vector2 point) {
	
}