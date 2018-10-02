#ifndef __VIEW_FLTK
#define __VIEW_FLTK
#define text_type 102
#include "IView.h"

#include "ViewHeaders.h"

#include "ViewMainWindow.h"
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

	static Inventory* inventory;
	
	static ViewLog* viewLog;

	static MainWindow* mainWindow;

	static DrawWindow* drawWindow;

	ViewFLTK();
	static ViewFLTK* instance;
public:
	static ViewFLTK* GetInstance();

	~ViewFLTK();

	IWidjet* GetWidjet(const typeWidjet);

	DisplayWidjet* GetWidjet(const string);

	void DeleteWidjet(const string);

#pragma region FunctionIview
	int Run();

	void DrawLine(const Vector2&, const Vector2&, typeDrawing);

	void DrawCircle(const Vector2&, const Vector2&, typeDrawing);

	void _DrawArc(const Vector2&, double, double, double);

	void DrawArc(const Vector2&, const Vector2&, const Vector2&, typeDrawing);

	void DrawPoint(const Vector2&);
	
	void SetColor(color);

	void SetColor(int, int, int);
	
	void Update();

	//for navigation on scene
	void TranslateScene(const Vector2&);

	void ScaleScene(const double&);

	void RotateScene(const double&);
	//_________________
#pragma endregion
};
#endif // !__VIEW_FLTK
