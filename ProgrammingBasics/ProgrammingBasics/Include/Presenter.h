#define SINGLE_SELECTION
#define POLY_SELECTION

#ifndef __PRESENTER
#define __PRESENTER

#include "Mode.h"

namespace DrawProject {

	class Presenter {
	private:
		Mode* mode;
		IView* view;
		Model* model;
		static Presenter* instance;

		Presenter();
	public:
		static Presenter* GetInstance();

		void Initializer(IView* _view);

		IView* GetView();

		void DrawScene();

		void DrawSelectedObjects(const Array<ID>&);

		void CleareScene();

		void MoveObject(const Array<ID>&, const Vector2&);

		void Compile(const std::string&);

		//function for view
		void Set_event(Event, Array<double>&, const std::string& str = "");
	};
}

#endif
