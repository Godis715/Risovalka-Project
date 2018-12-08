#ifndef __MODE
#define __MODE
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

	class CreateObject {
	protected:
		//enum TypeCreate { tCreate_segment, tCreate_point, tCreate_arc, tCreate_circle, tCreate };
		IView * view;
		Model* model;
		Undo_Redo* undo_redo;
		Color* color;
		bool isCreationFinish = false;
	public:
		bool IsCreationFinish();
		CreateObject();
		virtual ~CreateObject() {}
		virtual void DrawMode() = 0;
		virtual Array<ID> HandleEvent(const Event, Array<Vector2>&) = 0;
	};

	class CreatingSegment : public CreateObject {
	private:
		enum StateClick {
			noClick,
			oneClick
		};
		StateClick stateClick;
		Array<Vector2> segmentStartPoints;
		Array<Vector2> imaginaryPoints;
	public:
		CreatingSegment();
		~CreatingSegment();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};

	class CreatingStar : public CreateObject {
	private:
		enum StateClick {
			noClick,
			oneClick
		};
		StateClick stateClick;
		Array<ID> createdSegments;
		Array<ID> pointsToConnect;
		Array<Vector2> segmentStartPoints;
		Array<Vector2> imaginaryPoints;
	public:
		CreatingStar();
		~CreatingStar();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};

	class CreatingBrokenLine : public CreateObject {
	private:
		enum StateClick {
			noClick,
			oneClick
		};
		StateClick stateClick;
		Array<ID> createdSegments;
		Array<ID> pointsToConnect;
		Array<Vector2> segmentStartPoints;
		Array<Vector2> imaginaryPoints;
	public:
		CreatingBrokenLine();
		~CreatingBrokenLine();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};

	class CreatingPoint : public CreateObject
	{
	private:

	public:
		~CreatingPoint();

		CreatingPoint();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};

	class CreatingCircle : public CreateObject {
	private:
		enum StateClick { noClick, oneClick };
		StateClick stateClick;
		Array<Vector2> centerPoints;
		Array<Vector2> imaginaryPoints;
	public:
		CreatingCircle();

		~CreatingCircle();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};

	class CreatingArc : public CreateObject {
	private:
		enum StateClick { noClick, oneClick, twoClick };
		StateClick stateClick;
		Array<Vector2> centerPoints;
		Array<Vector2> startPoints;
		Array<Vector2> imaginaryPoints;
	public:
		CreatingArc();
		~CreatingArc();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};

	class CreatingCurve : public CreateObject {
	private:
		int countClick;
		bool isDrag;
		Array<Array<Vector2>> PointsCurves;

		Array<Vector2> connectPoints;
		Array<Vector2> controlPoints1;
		Array<Vector2> controlPoints2;
		Array<Vector2> imaginaryPoints;

		Event lastEvent;
	public:
		CreatingCurve();
		~CreatingCurve();

		Array<ID> HandleEvent(const Event, Array<Vector2>&);

		void DrawMode();
	};


	//---------------------------------

	class Mode {
	protected:
		Event lastEvent;

		Mode* UnexpectedEvent(const Event e, const Array<double>&);

		IView* view;
		Model* model;
		Color* color;
	public:
		Mode();
		void Init();
		virtual ~Mode() {}
		virtual Mode* HandleEvent(const Event, const Array<double>&) = 0;
		virtual void DrawMode() { }
	};

	class ChangingProperties : public Mode {
	private:
		IDisplayParamPrim * widjetPrim;
		IDisplayParamReq* widjetReq;
		ID selectedObject;
		Array<ID> reqIDs;
		ID reqID;
		Array<ID> primiOfReqIDs;
		bool isNew = true;
		enum State { none, click };
		State state;

		bool isChanged;
		Undo_Redo* undo_redo;
		Vector2 start;

		void SetWidjetParamPrim();

		void SetWidjetParamReq();
	public:
		ChangingProperties();
		ChangingProperties(const ID _selObjects);
		~ChangingProperties();

		Mode* HandleEvent(const Event e, const Array<double>& params);

		void DrawMode();
	};

	class Selection : public Mode {
	private:
		Array<ID> selectedObjects;
		enum State { single_selection, poly_selection, area_selection };
		State state;

		//for area selection
		Event lastEvent;
		Vector2 infoArea1;
		Vector2 infoArea2;
		ICreatingToolbar* widjet;

		void AddObject(const ID& obj);

		Array<string> GetPossibleReqType();
	public:
		Selection();
		Selection(ID);
		Selection(Array<ID>);
		~Selection();

		Mode* HandleEvent(const Event e, const Array<double>& params);

		void DrawMode();
	};

	class DMDefualt : public Mode
	{
	private:
		enum StateCreate { none, create };
		IDrawMode* outputWidjet;
		std::string nameMode;
		StateCreate stateCreate;

		CreateObject* createObject;

		Array<ID> selectionObjects;
	public:
		DMDefualt(Event);

		~DMDefualt();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	};

	class DMSymmetrical : public Mode
	{
	private:
		enum StateMode { ox2, oy2, o4, o8 };
		enum StateCreate { none, create };

		IDrawMode* outputWidjet;
		std::string nameMode;
		StateMode stateMode;
		StateCreate stateCreate;

		Vector2* pointRotate;

		CreateObject* createObject;

		Array<ID> selectionObjects;

		Array<Vector2> PointRotate(const Vector2&, const Vector2&);
	public:
		DMSymmetrical(Event, const Array<double>&);

		~DMSymmetrical();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	};

	class DMSectorSymmetrical : public Mode
	{
	private:
		enum StateCreate { none, create };
		IDrawMode* outputWidjet;
		std::string nameMode;
		StateCreate stateCreate;
		Vector2* pointRotate;
		CreateObject* createObject;
		Array<ID> selectionObjects;

		unsigned int countSector;
		double sinus;
		double cosinus;

		Array<Vector2> PointRotate(const Vector2&, const Vector2&);
	public:
		DMSectorSymmetrical(const Event, const Array<double>&);

		~DMSectorSymmetrical();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	};

	class Control {
	protected:
		Vector2 center;
	public:
		virtual bool IsClicked(double, double) = 0;
	};

	class RotationControl : public Control {
	private:

	public:
	};

	class RedactionCurve : public Mode {
	public:
		RedactionCurve(const ID&);
		~RedactionCurve();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	private:
		ID obj;
		Array<Vector2> points;
		Array<ID> pointsID;
		Array<Vector2> orts;
		Array<double> coefControls_1;
		Array<double> coefControls_2;

		Vector2 selectedPoint;
		int index;
		Vector2 start;
		Undo_Redo* undo_redo;
		ObjectController* ObjCtlr;

		enum State { none, addPoint, click, move };
		State state;
		bool isChanged;

		int GetPointOfCurve(const double, const double);
		int clickOnCurve(const double, const double);
		void AddPoint(const int, const double, const double);
		void ApplyChange();
	};

	class Redaction : public Mode {
	private:
		enum State { noClick, click };
		enum StatusRedaction { move, scale, rotate };
		Array<ID> selectedObjects;
		Vector2 posStart;
		Vector2 posEnd;
		Vector2 posLast;
		Vector2* pointRotate;
		double shiftBuffer;
		State state;
		StatusRedaction status;

		bool isChanged;
	public:
		// must take containers in constructor
		Redaction(Array<ID>, Event);
		~Redaction();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	};

	//class RedactionReq : public Mode {
	//private:
	//	Array<ID> objects;
	//	Array<ID> reqs;
	//	ID selectedReq;
	//	ID selectedPrim;
	//	Array<ID> objectsOfreq;
	//public:
	//	RedactionReq(ID _selecObj);
	//	RedactionReq();
	//	~RedactionReq();
	//
	//	Mode* HandleEvent(const Event, Array<double>&);
	//
	//	void DrawMode();
	//};

	class CreateRequirementWithParam : public Mode {
	private:
		Array<ID> selectedObjects;
		object_type typeRequirement;
		IRequirementInput* inputWidjet;
	public:
		CreateRequirementWithParam(Array<ID>, Event);
		CreateRequirementWithParam();
		~CreateRequirementWithParam();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	};

	class CreateDistBetPointsReq : public Mode {
	public:
		enum ModeType { pointDist, equalPointPos };
	private:
		enum State { firstPointSelected, pointNotSelected, secondPointSelected };
		State state;
		ModeType type;
		IDrawMode* outputWidjet;

		ID firstPoint;
		ID secondPoint;
		Vector2 currentCursorPos;
		IRequirementInput* inputWidjet;
	public:


		CreateDistBetPointsReq(ModeType);

		~CreateDistBetPointsReq();
		Mode * HandleEvent(const Event, const Array<double>&);
		void DrawMode();
	};

	class NavigationOnScene : public Mode {
	private:
		enum State { noClick, click };
		Array<ID> selectedPrim;
		Vector2 posStart;
		Vector2 posEnd;
		double speedMove;
		State stateMove;
	public:
		NavigationOnScene(Array<ID>);
		NavigationOnScene();
		~NavigationOnScene();

		Mode* HandleEvent(const Event, const Array<double>&);

		void DrawMode();
	};
}
#endif __MODE