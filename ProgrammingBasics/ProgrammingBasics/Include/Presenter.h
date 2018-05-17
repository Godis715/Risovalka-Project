#define SINGLE_SELECTION
#define POLY_SELECTION

#ifndef __PRESENTER

#include "IView.h"
#include "Model.h"
#include "Mode.h"

class Presenter {
private:
	static Mode* mode;
	static Model* model;
	static IView* view;
public:
	static void drawScene();

	//static void DrawSelected(const Array<ID>&){}

	static void Initializer(IView* _view);
	
	/* using for creating figures
	 points, segments, arcs, circles .. */
	static ID CreateObject(object_type, const Array<double>&);

	/* trying to impose requirements
	on selected object */

	static bool CreateRequirement(object_type, const Array<ID>&, const Array<double>&);
	static bool GetObject(double, double, ID&) { return true; }

	static void DeletePrimitives(const Array<ID>&);

	static void DeleteRequirement(const ID&);

	static void ChangeParamRequirement(const ID&, const double);

	static void ScaleObjects(const Array<ID>&, const double);

	static void MoveObject(const Array<ID>&, const Vector2&);

	/*static void ChangeObject(){}*/

	static void GetComponent(const ID&, Array<ID>&, Array<ID>&);

	//function for viewFLTK
	static void Set_event(Event, Array<double>&);
	
	static statusCreate status;
	static Array<Vector2> posClicks;
	static Array<double> params;

	static void changeStatusCreate(const statusCreate newStatus);

	static void clearScene();

	static void clickOnScene(double x, double y);
};
#endif
