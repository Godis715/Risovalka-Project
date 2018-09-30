#ifndef __VIEW_FLTK
#define __VIEW_FLTK
#define text_type 102
#include "IView.h"

#include "ViewHeaders.h"

#include "ViewDrawWindow.h"
#include "ViewToolbar.h"
#include "ViewLog.h"
#include "ViewFile.h"
#include "ViewDisplay.h"

typedef BinSearchTree<string, DisplayWidjet*> DataWidjet;

class ViewFLTK : public IView
{
private:
	DataWidjet* dataWidjet;

	static Fl_Window* mainWindow;
	
	static ViewLog* viewLog;

	ViewToolbar* viewToolbar;

	ViewFile* viewFile;

	static DrawWindow* drawWindow;

	/*class MainWindow : public Fl_Window
	{
	private:

	public:
		MainWindow(int x, int y, const char* name) : Fl_Window(x, y , name){}
		~MainWindow(){}
		int handle(int e)
		{
			if (e == FL_KEYDOWN || e == FL_KEYUP)
			{
				drawWindow->handle(e);
			}
			return e;
		}
	};*/

public:
	ViewFLTK();

	~ViewFLTK();

	//FuncIView
	int Run();

	void DrawLine(const Vector2&, const Vector2&, typeDrawing);

	void DrawCircle(const Vector2&, const Vector2&, typeDrawing);

	void _DrawArc(const Vector2&, double, double, double);

	void DrawArc(const Vector2&, const Vector2&, const Vector2&, typeDrawing);

	void DrawPoint(const Vector2&);
	
	void SetColor(color);
	
	void Update();

	//for navigation on scene
	void TranslateScene(const Vector2&);

	void ScaleScene(const double&);

	void RotateScene(const double&);
	//_________________
	IWidjet* GetWidjet(const typeWidjet);

	DisplayWidjet* GetWidjet(const string);
};
#endif // !__VIEW_FLTK
