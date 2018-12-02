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

	static Color* colorTheme;

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
	void DrawLine(const Array<double>&, typeDrawing);

	void DrawCircle(const Vector2&, const Vector2&, typeDrawing);
	void DrawCircle(const Array<double>&, typeDrawing);

	void _DrawArc(const Vector2&, double, double, double);

	void DrawArc(const Vector2&, const Vector2&, const Vector2&, typeDrawing);
	void DrawArc(const Array<double>&, typeDrawing);

	void DrawPoint(const Vector2&);
	void DrawPoint(const Array<double>&);

	void DrawCurve(const Array<Vector2>& points, typeDrawing type);
	void DrawCurve(const Array<double>& points, typeDrawing type);

	void DrawCurveNew(const Array<Vector2>& points, typeDrawing type);
	void DrawCurveNew(const Array<double>& points, typeDrawing type);

	void SetColor(const int, const int, const int);
	void SetColor(const rgbColor);
	
	void Update();

	//for navigation on scene
	void TranslateScene(const Vector2&);

	void ScaleScene(const double&);

	void RotateScene(const double&);
	//_________________
#pragma endregion
};
#endif // !__VIEW_FLTK
