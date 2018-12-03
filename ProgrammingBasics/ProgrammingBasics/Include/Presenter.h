#define SINGLE_SELECTION
#define POLY_SELECTION

#ifndef __PRESENTER
#define __PRESENTER

#include "Mode.h"

class Presenter {
private:
	static Mode* mode;
	static IView* view;
	static Model* model;
public:
	static IView* GetView();

	static void DrawScene();

	static void DrawSelectedObjects(const Array<ID>&);

	static void Initializer(IView* _view);

	static void CleareScene();

	static void MoveObject(const Array<ID>&, const Vector2&);

	static void Compile();

	//function for view
	static void Set_event(Event, Array<double>&, const std::string& str = "");
};



#endif
