#ifndef __VIEW_WPF
#define __VIEW_WPF

#include "IView.h"
#include "Presenter.h"
#include "WPFWidget.h"

using namespace Kernel;

namespace DrawProject {

	class ViewWPF : public IView {

	public:
		void DrawPoint(const Array<double>&);
		void DrawLine(const Array<double>&);
		void DrawArc(const Array<double>&);
		void DrawCircle(const Array<double>&);
		void DrawCurve(const Array<double>&);

		void SetStyleDrawing(const rgbColor, const typeDrawing = null);

		int Run();
		void Update();

		void TranslateScene(const Vector2&);
		void ScaleScene(const double&);
		void RotateScene(const double&);

		IWidjet* GetWidjet(const typeWidjet);

		static ViewWPF* GetInstance();
	private:
		ViewWPF();

		MailBox* mailBox;

		static ViewWPF* instance;
	};
}

#endif