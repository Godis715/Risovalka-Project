#define SINGLE_SELECTION
#define POLY_SELECTION

#ifndef __PRESENTER
#define __PRESENTER

#include "IView.h"
#include "Model.h"
#include "Mode.h"


class Presenter {
private:
	static Mode* mode;
	static Model* model;
	static IView* view;
public:
	static void SaveProject(std::string);
	static void DownloadFile(std::string);
	static IView* GetView();
	static void DrawScene();
	static void DrawSelectedObjects(const Array<ID>&);

	//static void DrawObject(const ID&, color);

	//static void DrawSelected(const Array<ID>&){}

	static bool GetObjType(const ID&, object_type&);

	static bool GetObjParam(const ID&, Array<double>&);

	static void Initializer(IView* _view);
	
	/* using for creating figures
	 points, segments, arcs, circles .. */
	static ID CreateObject(object_type, const Array<double>&);

	/* trying to impose requirements
	on selected object */

	static ID CreateRequirement(object_type, const Array<ID>&, const Array<double>&);

	static bool GetObject(double, double, ID&);

	static bool GetObjectsOnArea(double, double, double, double, Array<ID>&);

	static void DeletePrimitives(const Array<ID>&);

	static void DeleteRequirement(const ID&);

	static void CleareScene();

	static void ChangeParamRequirement(const ID&, const double);

	static void ScaleObjects(const Array<ID>&, const double);

	static void MoveObject(const Array<ID>&, const Vector2&);

	/*static void ChangeObject(){}*/

	static void GetComponent(const ID&, Array<ID>&, Array<ID>&);

	static void Compile();

	//function for viewFLTK
	static void Set_event(Event, Array<double>&);
};



#endif
