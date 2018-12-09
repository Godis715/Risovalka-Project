#ifndef __IMODE
#define __IMODE

#include "IView.h"
#include "Model.h"
#include <sstream>
#include <iomanip>

namespace DrawProject {

	double Parse(string);

	const char* ReverseParse(const double, int&);

	const string ReverseParse(const double);

	const char* str_ch(const string);

	enum Event
	{
		// create primitive
		ev_createPoint = 1,
		ev_createSegment,
		ev_createStar,
		ev_createBrokenLine,
		ev_createArc,
		ev_createCircle,
		ev_createCurve,
		// drawingMode
		ev_symmetricalDraw,
		ev_defualtDraw,
		ev_rotationDraw,
		//create requirements
		ev_req_D_point,
		ev_req_Eq_Segment,
		ev_req_on_one_hand,
		ev_req_D_point_segment,
		ev_req_D_point_arc,
		ev_req_angle_segment,
		ev_input,
		//fase create requirements
		ev_req_D_point_fast,
		ev_req_Eq_point_fast,
		// redaction
		ev_moveObjects,
		ev_scaleObjects,
		ev_rotateObjects,
		ev_del,
		ev_delAll,
		ev_undo,
		ev_redu,

		// mouseEvent
		ev_leftMouseClick,
		ev_rightMouseClick,
		ev_leftMouseDown,
		ev_rightMouseDown,
		ev_leftMouseUp,
		ev_rightMouseUp,
		ev_mouseMove,
		ev_scroll,
		// keyboardEvent
		ev_ctrlDown,
		ev_ctrlUp,
		ev_altDown,
		ev_altUp,
		ev_arrowUp,
		ev_arrowDown,
		ev_arrowLeft,
		ev_arrowRight,
		ev_escape,
		ev_enter,
		// Widjets
		ev_click_Req,
		ev_change_Prim,
		ev_change_Req,
		ev_delete_Req,
		ev_delete_display_Prim,
		ev_delete_display_Req,
		// file work
		ev_save,
		ev_download,
		ev_compile,
		ex_set_theme
	};

	class Mode {
	protected:
		Event lastEvent;

		Mode* UnexpectedEvent(const Event e, const Array<double>&);

		IView* view;
		Presenter* presenter;
		Model* model;
		Color* color;
	public:
		Mode();
		virtual ~Mode() {}
		virtual Mode* HandleEvent(const Event, const Array<double>&) = 0;
		virtual void DrawMode() { }
	};
}
#endif __MODE