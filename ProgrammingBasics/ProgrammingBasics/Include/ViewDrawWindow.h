#ifndef __VIEW_DRAWWINDOW
#define __VIEW_DRAWWINDOW
#include "ViewHeaders.h"
#include "ViewLog.h"

class DrawWindow : public Fl_Double_Window, public DisplayWidjet
{
private:
	static ViewLog* viewLog;

	static Inventory* inventory;

	static Vector2* translateScene;
	
	static double scaleScene;

	static double rotateScene;

	Fl_Output* drawCoord;

	void draw();

public:
	DrawWindow(int, int, int, int, const char *);

	~DrawWindow();

	int handle(int);

	void TranslateScene(const Vector2&);

	void ScaleScene(const double&);

	void RotateScene(const double&);
};

#endif __VIEW_DRAWWINDOW
