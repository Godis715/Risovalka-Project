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
	static void SaveProject(const std::string&);
	static void DownloadFile(const std::string&);
	static IView* GetView();
	static void DrawScene();
	static void DrawSelectedObjects(const Array<ID>&);

	static void Initializer(IView* _view);

	static void CleareScene();



	static void MoveObject(const Array<ID>&, const Vector2&);

	static void Compile();

	static void Update();

	static void Set_event(Event, Array<double>&);
};



#endif
