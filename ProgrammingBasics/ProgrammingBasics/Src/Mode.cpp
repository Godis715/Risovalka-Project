#include "Mode.h"
#include "Presenter.h"

#pragma region OtherFunction
string objTypeToString(const object_type type)
{
	switch (type)
	{
	case ot_point: {
		return string("point");
	}
	case ot_segment: {
		return string("segment");
	}
	case ot_arc: {
		return string("arc");
	}
	case ot_circle: {
		return string("circle");
	}
	case ot_distBetPoints: {
		return string("distBetPoints");
	}
	case ot_equalSegmentLen: {
		return string("equalSegmentLen");
	}
	case ot_pointsOnTheOneHand: {
		return string("pointsOnTheOneHand");
	}
	case ot_distBetPointSeg: {
		return string("distBetPointSeg");
	}
	case ot_pointPosReq: {
		return string("pointPosReq");
	}
	case ot_angleBetSeg: {
		return string("angleBetSeg");
	}
	case ot_distBetPointArc: {
		return string("distBetPointArc");
	}
	case ot_pointInArc: {
		return string("pointInArc");
	}
	default:
		return string("");
	}
}

double Parse(string number) {
	int countPoint = 0;
	if (number[0] == 'e' || number[0] == '.') {
		return -1;
	}

	for (size_t i = 1; i < number.length(); ++i) {
		if (number[i] == 'e' || number[i] == '-') {
			return -1;
		}
		if (number[i] == '.') {
			++countPoint;
			if (countPoint > 1) {
				return -1;
			}
		}
	}
	return stod(number);
}

const char* ReverseParse(const double dig, int& size)
{
	std::string strDig;
	std::ostringstream ost;
	ost << std::fixed << std::setprecision(2) << dig;
	strDig = ost.str();

	size = strDig.length();
	char* charDig = new char[size];
	for (int i = 0; i < size; i++)
	{
		charDig[i] = strDig[i];
	}
	return charDig;
}

const string ReverseParse(const double dig) {
	std::string strDig;
	std::ostringstream ost;
	ost << std::fixed << std::setprecision(2) << dig;
	strDig = ost.str();

	return strDig;
}

const char* str_ch(const string str) {
	char* charDig = new char[str.length() + 1];
	for (int i = 0; i < str.length(); i++)
	{
		charDig[i] = str[i];
	}
	charDig[str.length()] = '\0';
	return charDig;
}
#pragma endregion

#pragma region Mode
Mode* Mode::UnexpectedEvent(const Event e) {
	switch (e) {
	case ev_symmetricalDraw:{
		return new DrawingModes(e);
	}
	case ev_defualtDraw: {
		return new DrawingModes(e);
	}
	case ev_createPoint: {
		return new DrawingModes(e);
	}
	case ev_createArc: {
		return new DrawingModes(e);
	}
	case ev_createSegment: {
		return new DrawingModes(e);
	}
	case ev_createCircle: {
		return new DrawingModes(e);
	}
	case ev_mouseMove:
		return nullptr;
	case ev_leftMouseUp:
		return nullptr;
	case ev_ctrlDown:
		return nullptr;
	case ev_ctrlUp:
		return nullptr;
	case ev_undo: {
		auto undo_redo = Undo_Redo::GetInstance();
		undo_redo->Undo();
		return new Selection();
	}
	case ev_redu: {
		auto undo_redo = Undo_Redo::GetInstance();
		undo_redo->Redo();
		return new Selection();
	}
	default:
		return new Selection();
	}
}

Mode::Mode() {
	model = Model::GetInstance();
	view = Presenter::GetView();
}
#pragma endregion

#pragma region Changing_Properties
ChangingProperties::ChangingProperties() : Mode()
{}

ChangingProperties::ChangingProperties(const ID _selObject) : Mode(), selectedObject(_selObject)
{
	widjetPrim = static_cast<IDisplayParamPrim*>(view->GetWidjet(displayParamPrim));
	SetWidjetParamPrim();
}

ChangingProperties::~ChangingProperties()
{
	if (isNew) {
		delete widjetPrim;
		delete widjetReq;
	}
}

void ChangingProperties::SetWidjetParamPrim() {
	object_type typePrim = model->GetObjType(selectedObject);

	Array<double> params;

	Array<string> paramsString;
	switch (typePrim)
	{
	case ot_point:
	{
		params = model->GETVARPARAMS(selectedObject, VERTEX);
		break;
	}
	case ot_segment:
	{
		params = model->GETVARPARAMS(selectedObject, VERTEX);
		break;
	}
	case ot_arc:
	{
		params = model->GETVARPARAMS(selectedObject, VERTEX, ANGLE);
		params[4] = params[4] * 180 / PI;
		break;
	}
	case ot_circle:
	{
		params = model->GETVARPARAMS(selectedObject, CENTER, RADIUS);
		break;
	}
	default:
		break;
	}
	paramsString = Array<string>(params.GetSize());
	for (int i = 0; i < params.GetSize(); ++i) {
		paramsString[i] = ReverseParse(params[i]);
	}

	reqIDs.Clear();
	reqIDs = model->GetRelatedObjects(selectedObject);

	Array<string> nameReqs;
	for (int i = 0; i < reqIDs.GetSize(); i++)
	{
		object_type typeReq = model->GetObjType(reqIDs[i]);
		nameReqs.PushBack(objTypeToString(typeReq) + '#' + reqIDs[i].GetHash());
	}

	widjetPrim->SetParam(paramsString, nameReqs);
}

void ChangingProperties::SetWidjetParamReq() {
	primiOfReqIDs = model->GetRelatedObjects(reqID);

	Array<double> reqParams = model->GetObjParam(reqID);

	auto reqStringParams = Array<string>(reqParams.GetSize());
	for (int i = 0; i < reqParams.GetSize(); ++i) {
		reqStringParams[i] = ReverseParse(reqParams[i]);
	}

	object_type type = model->GetObjType(reqID);

	widjetReq->SetParam(reqStringParams, objTypeToString(type));
}

Mode* ChangingProperties::HandleEvent(const Event e, Array<double>& params)
{
	switch (e)
	{
	case ev_click_Req:
	{
		reqID = reqIDs[int(params[0])];
		widjetReq = static_cast<IDisplayParamReq*>(view->GetWidjet(displayParamReq));
		SetWidjetParamReq();
		return nullptr;
	}
	case ev_change_Prim:
	{
		switch (model->GetObjType(selectedObject))
		{
		case ot_point:
		{
			model->SETVARPARAMS(selectedObject, params, VERTEX);
			break;
		}
		case ot_segment:
		{
			model->SETVARPARAMS(selectedObject, params, VERTEX);
			break;
		}
		case ot_arc:
		{
			params[4] = params[4] * PI / 180;
			model->SETVARPARAMS(selectedObject, params, VERTEX, ANGLE);
			break;
		}
		case ot_circle:
		{
			model->SETVARPARAMS(selectedObject, params, CENTER, RADIUS);
			break;
		}
		default:
			break;
		}
		SetWidjetParamPrim();
		return nullptr;
	}
	case ev_change_Req:
	{
		model->ChangeRequirement(reqID, params);
		SetWidjetParamReq();
		SetWidjetParamPrim();
		return nullptr;
	}
	case ev_delete_Req:
	{
		model->DeleteObject(reqID);
		SetWidjetParamPrim();
		reqID = ID();
		delete widjetReq;
		widjetReq = nullptr;
		return nullptr;
	}
	case ev_rightMouseDown:
	{
		ID obj = model->GetObjectByClick(params[0], params[1]);
		if (!IDGenerator::IsNullID(obj))
		{
			isNew = false;
			delete widjetPrim;
			delete widjetReq;
			return new ChangingProperties(obj);
		}
		return nullptr;
	}
	case ev_delete_display_Prim: {
		return new Selection(selectedObject);
	}
	case ev_delete_display_Req: {
		reqID = ID();
		delete widjetReq;
		widjetReq = nullptr;
		return nullptr;
	}
	case ev_escape: {
		return new Selection(selectedObject);
	}
	default:
		return UnexpectedEvent(e);
	}
}

void ChangingProperties::DrawMode()
{
	Array<ID> selectedObjects;
	selectedObjects.PushBack(selectedObject);
	view->SetColor(col_Aqua);
	Presenter::DrawSelectedObjects(primiOfReqIDs);
	view->SetColor(col_Orange);
	Presenter::DrawSelectedObjects(selectedObjects);
	
}
#pragma endregion

#pragma region DrawingModes
DrawingModes::DrawingModes(Event e) : selectionObjects(0)
{
	pointRotate = nullptr;
	stateCreate = createNone;
	switch (e)
	{
	case ev_createPoint: {
		stateMode = defualtDraw;
		stateCreate = createPoint;
		createObject = new CreatingPoint();
		break;
	}
	case ev_createSegment: {
		stateMode = defualtDraw;
		stateCreate = createSegment;
		createObject = new CreatingSegment();
		break;
	}
	case ev_createArc: {
		stateMode = defualtDraw;
		stateCreate = createArc;
		createObject = new CreatingArc();
		break;
	}
	case ev_createCircle: {
		stateMode = defualtDraw;
		stateCreate = createCircle;
		createObject = new CreatingCircle();
		break;
	}
	case ev_symmetricalDraw: {
		stateMode = symmetricalDraw;
		break;
	}
	case ev_defualtDraw: {
		stateMode = defualtDraw;
		break;
	}
	default:
		break;
	}
}

DrawingModes::~DrawingModes(){}

void DrawingModes::PointRotate(const Vector2& point, Array<Vector2>& resultPoints, const Vector2& center)
{
	resultPoints.PushBack(point);
	resultPoints.PushBack(Vector2((point - center).x * -1, (point - center).y) + center);
	resultPoints.PushBack(Vector2((point - center).x, (point - center).y * -1) + center);
	resultPoints.PushBack(Vector2((point - center).x * -1, (point - center).y * -1) + center);
}

Mode* DrawingModes::HandleEvent(const Event ev, Array<double>& params)
{
	switch (stateMode)
	{
	case symmetricalDraw:
	{
		switch (ev)
		{
		case ev_leftMouseDown:
		{
			if (params.GetSize() != 2) {
				throw std::invalid_argument("Bad number of parameters");
			}
			if (stateCreate == createNone)
			{
				selectionObjects.Clear();
				delete pointRotate;
				pointRotate = new Vector2(params[0], params[1]);
			}
			else if (pointRotate != nullptr)
			{
				Array<Vector2>points;
				PointRotate(Vector2(params[0], params[1]), points, *pointRotate);
				Array<ID> objIDs = createObject->HandleEvent(ev, points);
				if (objIDs.GetSize() != 0)
				{
					selectionObjects += objIDs;
					stateCreate = createNone;
					delete createObject;
					createObject = nullptr;
				}
			}
			else
			{
				pointRotate = new Vector2(params[0], params[1]);
			}
			return nullptr;
		}
		case ev_mouseMove:
		{
			if (stateCreate != createNone)
			{
				Array<Vector2>points;
				PointRotate(Vector2(params[0], params[1]), points, *pointRotate);
				Array<ID> objIDs = createObject->HandleEvent(ev, points);
				if (objIDs.GetSize() != 0)
				{
					throw std::exception("Error!");
				}
			}
			return nullptr;
		}
		default:
			break;
		}
	}
	case defualtDraw:
	{
		switch (ev)
		{
		case ev_leftMouseDown:
		{
			if (params.GetSize() != 2) {
				throw std::invalid_argument("Bad number of parameters");
			}
			if (stateCreate == createNone)
			{
				selectionObjects.Clear();
				return new Selection();
			}
			else
			{
				Array<Vector2>points;
				points.PushBack(Vector2(params[0], params[1]));
				Array<ID> objIDs = createObject->HandleEvent(ev, points);
				if (objIDs.GetSize() != 0)
				{
					selectionObjects += objIDs;
					stateCreate = createNone;
					delete createObject;
					createObject = nullptr;
				};
			}
			return nullptr;
		}
		case ev_mouseMove:
		{
			if (stateCreate != createNone)
			{
				Array<Vector2>points;
				points.PushBack(Vector2(params[0], params[1]));
				Array<ID> objIDs = createObject->HandleEvent(ev, points);
				if (objIDs.GetSize() != 0)
				{
					throw std::exception("Error!");
				}
			}
			return nullptr;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	switch (ev)
	{
	case ev_createArc:
	{
		stateCreate = createArc;
		createObject = new CreatingArc();
		return nullptr;
	}
	case ev_createCircle:
	{
		stateCreate = createCircle;
		createObject = new CreatingCircle();
		return nullptr;
	}
	case ev_createSegment:
	{
		stateCreate = createSegment;
		createObject = new CreatingSegment();
		return nullptr;
	}
	case ev_createPoint:
	{
		stateCreate = createPoint;
		createObject = new CreatingPoint();
		return nullptr;
	}
	case ev_symmetricalDraw:
	{
		stateMode = symmetricalDraw;
		return nullptr;
	}
	case ev_defualtDraw:
	{
		delete pointRotate;
		pointRotate = nullptr;
		stateMode = defualtDraw;
		return nullptr;
	}
	case ev_escape:
		return new Selection(selectionObjects);
	default:
		break;
	}
	return UnexpectedEvent(ev);
}

void DrawingModes::DrawMode()
{
	if (pointRotate != nullptr)
	{
		view->SetColor(col_Blue);
		view->DrawPoint(Vector2(pointRotate->x, pointRotate->y));
	}
	if (createObject != nullptr)
	{
		createObject->DrawMode();
	}
	if (selectionObjects.GetSize() != 0)
	{
		view->SetColor(col_Green);
		Presenter::DrawSelectedObjects(selectionObjects);
	}
}
#pragma endregion

#pragma region Selection
Selection::Selection(Array<ID> _selObjects) : Mode(), selectedObjects(_selObjects) {
	state = single_selection;
	widjet = static_cast<ICreatingToolbar*>(view->GetWidjet(creatingToolbar));
	if (selectedObjects.GetSize() == 1) {
		widjet->Clear();
	}
	else {
		widjet->SetParam(GetPossibleReqType());
	}
}

Selection::Selection() : Mode(), selectedObjects(0) {
	widjet = static_cast<ICreatingToolbar*>(view->GetWidjet(creatingToolbar));
	state = single_selection;
	widjet->Clear();
}

Selection::Selection(ID id) {
	selectedObjects = Array<ID>(1);
	selectedObjects[0] = id;
	state = single_selection;
	widjet = static_cast<ICreatingToolbar*>(view->GetWidjet(creatingToolbar));
	widjet->Clear();
}

Selection::~Selection() {
	selectedObjects.Clear();
	delete widjet;
}

void Selection::AddObject(const ID& obj) {
	for (int i = 0; i < selectedObjects.GetSize(); ++i) {
		if (selectedObjects[i] == obj) {
			selectedObjects.EraseO_1_(i);
			return;
		}
	}
	selectedObjects.PushBack(obj);
}

Array<string> Selection::GetPossibleReqType() {
	int points = 0;
	int segments = 0;
	int circles = 0;
	int arcs = 0;
	for (int i = 0; i < selectedObjects.GetSize(); ++i) {
		object_type typePrim = model->GetObjType(selectedObjects[i]);
		switch (typePrim)
		{
		case ot_point: {
			++points;
			break;
		}
		case ot_segment: {
			++segments;
			break;
		}
		case ot_circle: {
			++circles;
			break;
		}
		case ot_arc: {
			++arcs;
			break;
		}
		default:
			break;
		}
	}
	Array<string> nameTypeReqs;

	if ((points == 2) && (segments == 0) &&
		(circles == 0) && (arcs == 0)) {
		nameTypeReqs.PushBack("Dist points");
	}
	if ((points == 0) && (segments == 2) &&
		(circles == 0) && (arcs == 0)) {
		nameTypeReqs.PushBack("Equal segment");
	}
	if ((points == 2) && (segments == 1) &&
		(circles == 0) && (arcs == 0)) {
		nameTypeReqs.PushBack("Points on one hand");
	}
	if ((points == 1) && (segments == 1) &&
		(circles == 0) && (arcs == 0)) {
		nameTypeReqs.PushBack("Dist point segment");
	}
	if ((points == 1) && (segments == 0) &&
		(circles == 0) && (arcs == 1)) {
		nameTypeReqs.PushBack("Dist point arc");
	}
	if ((points == 0) && (segments == 2) &&
		(circles == 0) && (arcs == 0)) {
		nameTypeReqs.PushBack("Angle between segment");
	}
	return nameTypeReqs;
}

Mode* Selection::HandleEvent(const Event e, Array<double>& params) {
	if (e == ev_rightMouseDown)
	{
		selectedObjects.Clear();
		ID obj = model->GetObjectByClick(params[0], params[1]);
		if (!IDGenerator::IsNullID(obj))
		{
			return new ChangingProperties(obj);
		}
		return nullptr;
	
	}
	if (e == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}

		//for area selection
		lastEvent = e;
		infoArea1.x = params[0];
		infoArea1.y = params[1];

		ID obj = model->GetObjectByClick(params[0], params[1]);
		if (!IDGenerator::IsNullID(obj)) {
			if (state == single_selection) {
				selectedObjects.Clear();
				selectedObjects.PushBack(obj);
				widjet->Clear();
				return nullptr;
			}

			if (state == poly_selection) {
				AddObject(obj);
				widjet->SetParam(GetPossibleReqType());
				return nullptr;
			}
		}
		else {
			if (state != poly_selection)
			{
				widjet->Clear();
				selectedObjects.Clear();
			}
			return nullptr;
		}
		
	}

	//for area selection
	if (e == ev_mouseMove && (lastEvent == ev_leftMouseDown || lastEvent == ev_mouseMove) && state != poly_selection)
	{
		state = area_selection;
		infoArea2.x = params[0];
		infoArea2.y = params[1];
		selectedObjects.Clear();
		lastEvent = e;
		selectedObjects = model->GetObjectsByArea(infoArea1.x, infoArea1.y, infoArea2.x, infoArea2.y);
		return nullptr;
	}
	if (e == ev_leftMouseUp)
	{
		if (lastEvent == ev_mouseMove)
		{
			state = single_selection;
			widjet->SetParam(GetPossibleReqType());
		}
		lastEvent = e;
		return nullptr;
	}
	
	switch (e)
	{
	case ev_ctrlDown: {
		state = poly_selection;
		return nullptr;
	}
	case ev_ctrlUp: {
		state = single_selection;
		return nullptr;
	}
	case ev_altDown: {
		return new NavigationOnScene(selectedObjects);
	}
	case ev_escape: {
		selectedObjects.Clear();
		return nullptr;
	}
	case ev_moveObjects: {
		if (selectedObjects.GetSize() == 0) {
			return nullptr;
		}
		return new Redaction(selectedObjects, ev_moveObjects);
	}
	case ev_scaleObjects: {
		if (selectedObjects.GetSize() == 0) {
			return nullptr;
		}
		return new Redaction(selectedObjects, ev_scaleObjects);
	}
	case ev_del: {
		model->DeleteObjects(selectedObjects);
		selectedObjects.Clear();
		return nullptr;
	}
	case ev_req_D_point: {
		return new CreateRequirementWithParam(selectedObjects, e);
	}
	case ev_req_D_point_segment: {
		return new CreateRequirementWithParam(selectedObjects, e);
	}
	case ev_req_D_point_arc: {
		return new CreateRequirementWithParam(selectedObjects, e);
	}
	case ev_req_angle_segment: {
		return new CreateRequirementWithParam(selectedObjects, e);
	}
	case ev_req_Eq_Segment: {
		Array<double>param(0);

		model->CreateRequirement(ot_equalSegmentLen, selectedObjects, param);
		return nullptr;
	}
	case ev_req_on_one_hand: {
		Array<double>param(0);

		model->CreateRequirement(ot_pointsOnTheOneHand, selectedObjects, param);
		return nullptr;
	}
	default:
		return UnexpectedEvent(e);
	}
}

void Selection::DrawMode()
{
	view->SetColor(col_Green);
	Presenter::DrawSelectedObjects(selectedObjects);

	if (state == area_selection)
	{
		Vector2 point1(infoArea2.x, infoArea1.y);
		Vector2 point2(infoArea1.x, infoArea2.y);

		view->SetColor(col_Blue);
		view->DrawLine(infoArea1, point1, points);
		view->DrawLine(infoArea1, point2, points);
		view->DrawLine(infoArea2, point1, points);
		view->DrawLine(infoArea2, point2, points);
	}
}
#pragma endregion

#pragma region Redaction
Redaction::Redaction(Array<ID> _selecObj, Event _ev) : selectedObjects(_selecObj){
	state = noClick;
	switch (_ev)
	{
	case ev_moveObjects:
		status = move;
		break;
	case ev_scaleObjects:
	{
		status = scale;
		break;
	}
	default:
        std::invalid_argument("Redaction : not valid status");
		break;
	}
}

Redaction::~Redaction() {
	selectedObjects.Clear();
}

Mode* Redaction::HandleEvent(const Event e, Array<double>& params)
{
	if (status == move)
	{
		if (e == ev_leftMouseDown) {
			if (params.GetSize() != 2) {
                throw std::invalid_argument("Bad number of parameters");
			}
			posStart.x = params[0];
			posStart.y = params[1];
			state = click;
			posEnd = posStart;
			return nullptr;
		}
		if (e == ev_mouseMove && state == click)
		{
			if (params.GetSize() != 2) {
                throw std::invalid_argument("Bad number of parameters");
			}

			Vector2 last = posEnd;

			posEnd.x = params[0];
			posEnd.y = params[1];

			shiftBuffer = shiftBuffer + Vector2::Dot(posEnd - last, posEnd - last);

			if (shiftBuffer > 4.0) {
				model->Move(selectedObjects, posEnd - posStart);
				shiftBuffer = 0.0;

				posStart = posEnd;
			}
			return nullptr;
		}
		if (e == ev_leftMouseUp) {
			state = noClick;
			return nullptr;
		}
	}
	if (status == scale)
	{
		if (e == ev_scroll)
		{
			if (params.GetSize() != 1) {
                throw std::invalid_argument("Bad number of parameters");
			}
			double coef;
			if (params[0] > 0 )
			{
				coef = 0.9;
			}
			if (params[0] < 0)
			{
				coef = 1.1;
			}
			model->Scale(selectedObjects, coef);
			return nullptr;
		}
	}
	if (e == ev_escape)
	{
		model->Move(selectedObjects, posEnd - posStart);
		return new Selection(selectedObjects);
	}
	if (e == ev_scaleObjects)
	{
		model->Move(selectedObjects, posEnd - posStart);
		return new Redaction(selectedObjects, ev_scaleObjects);
	}
	if (e == ev_moveObjects)
	{
		model->Move(selectedObjects, posEnd - posStart);
		return new Redaction(selectedObjects, ev_moveObjects);
	}
	if (e == ev_del)
	{
		model->DeleteObjects(selectedObjects);
		return new Selection();
	}
	return UnexpectedEvent(e);
}

void Redaction::DrawMode() {
	view->SetColor(col_Green);
	Presenter::DrawSelectedObjects(selectedObjects);
}
#pragma endregion

//RedactionReq::RedactionReq(ID _selecObj) : selectedPrim(_selecObj) {
//	model->GetComponent(selectedPrim, objects, reqs);
//}
//
//RedactionReq::RedactionReq() { }
//
//RedactionReq::~RedactionReq() {
//	objects.Clear();
//	reqs.Clear();
//	objectsOfreq.Clear();
//}
//
//Mode* RedactionReq::HandleEvent(const Event ev, Array<double>& param) {
//	return nullptr;
//}
//
//void RedactionReq::DrawMode() {
//
//}

#pragma region CreateRequirementWithParam
CreateRequirementWithParam::CreateRequirementWithParam(Array<ID> _selecObj, Event _ev) : selectedObjects(_selecObj) {
	inputWidjet = static_cast<IRequirementInput*>(view->GetWidjet(requirementInput));
	switch (_ev)
	{
	case ev_req_D_point: {
		typeRequirement = ot_distBetPoints;
		break;
	}
	case ev_req_D_point_segment: {
		typeRequirement = ot_distBetPointSeg;
		break;
	}
	case ev_req_D_point_arc: {
		typeRequirement = ot_distBetPointArc;
		break;
	}
	case ev_req_angle_segment: {
		typeRequirement = ot_angleBetSeg;
		break;
	}
	default:
		std::invalid_argument("CreateRequirement : not valid status");
		break;
	}
}

CreateRequirementWithParam::CreateRequirementWithParam() {
	inputWidjet = static_cast<IRequirementInput*>(view->GetWidjet(requirementInput));
}

CreateRequirementWithParam::~CreateRequirementWithParam() {
	delete inputWidjet;
}

Mode* CreateRequirementWithParam::HandleEvent(const Event ev, Array<double>& params) {
	switch (ev) {
	case ev_input:
	{
		if (params.GetSize() != 1) {
			throw std::invalid_argument("Bad number of parameters");
		}

		model->CreateRequirement(typeRequirement, selectedObjects, params);

		return new Selection(selectedObjects);

	}
	case ev_escape:
	{
		return new Selection(selectedObjects);
	}
	case ev_moveObjects:
	{
		return new Redaction(selectedObjects, ev_moveObjects);
	}
	case ev_scaleObjects:
	{
		return new Redaction(selectedObjects, ev_scaleObjects);
	}
	case  ev_del:
	{
		model->DeleteObjects(selectedObjects);
		return new Selection();
	}
	default:
		return UnexpectedEvent(ev);
	}
}
	

void CreateRequirementWithParam::DrawMode() {
	view->SetColor(col_Green);
	Presenter::DrawSelectedObjects(selectedObjects);
}
#pragma endregion

#pragma region NavigationOnScene
NavigationOnScene::NavigationOnScene(Array<ID> _selecObj) : selectedPrim(_selecObj) { 
	stateMove =  noClick;
	speedMove = 10;
}

NavigationOnScene::NavigationOnScene() { }

NavigationOnScene::~NavigationOnScene() { }

Mode* NavigationOnScene::HandleEvent(const Event ev, Array<double>& params) {
	//for translate 
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		posStart.x = params[0];
		posStart.y = params[1];
		stateMove = click;
		posEnd = posStart;
		return nullptr;
	}
	if (ev == ev_mouseMove && stateMove == click)
	{
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		posEnd.x = params[0];
		posEnd.y = params[1];
		view->TranslateScene(posEnd - posStart);
		posStart = posEnd;
		return nullptr;
	}
	if (ev == ev_leftMouseUp) {
		stateMove = noClick;
		return nullptr;
	}

	if (ev == ev_arrowUp)
	{
		view->TranslateScene(Vector2(0, -speedMove));
		return nullptr;
	}
	if (ev == ev_arrowDown)
	{
		view->TranslateScene(Vector2(0, speedMove));
		return nullptr;
	}
	if (ev == ev_arrowLeft)
	{
		view->TranslateScene(Vector2(-speedMove, 0));
		return nullptr;
	}
	if (ev == ev_arrowRight)
	{
		view->TranslateScene(Vector2(speedMove, 0));
		return nullptr;
	}
	
	//for scale
	if (ev == ev_scroll)
	{
		if (params.GetSize() != 1) {
            throw std::invalid_argument("Bad number of parameters");
		}
		double deltaCoef;
		if (params[0] > 0)
		{
			deltaCoef = -0.1;
		}
		if (params[0] < 0)
		{
			deltaCoef = 0.1;
		}
		view->ScaleScene(deltaCoef);
		return nullptr;
	}

	//for rotate
	//..

	//exit
	if (ev == ev_altUp)
	{
		return new Selection(selectedPrim);
	}

	return UnexpectedEvent(ev);
}

void NavigationOnScene::DrawMode() {
	view->SetColor(col_Green);
	Presenter::DrawSelectedObjects(selectedPrim);
}
#pragma endregion

#pragma region CreateObject
CreateObject::CreateObject() {
	model = Model::GetInstance();
	view = Presenter::GetView();
	undo_redo = Undo_Redo::GetInstance();
}
#pragma endregion

#pragma region CreatingSegment
CreatingSegment::CreatingSegment() {
	stateClick = noClick;
}

Array<ID> CreatingSegment::HandleEvent(const Event ev, Array<Vector2>& params) {
	switch (ev)
	{
	case ev_leftMouseDown:
	{
		switch (stateClick)
		{
		case noClick:
		{
			for (int i = 0; i < params.GetSize(); i++)
			{
				segmentStartPoints.PushBack(params[i]);
			}
			stateClick = oneClick;
			return Array<ID>(0);
		}
		case oneClick:
		{
			if (params.GetSize() != segmentStartPoints.GetSize())
			{
				throw std::invalid_argument("Bad number of parameters");
			}
			Array<ID>segIDs(segmentStartPoints.GetSize());
			for (int i = 0; i < params.GetSize(); i++)
			{
				Array<double> segmentParameters(4);
				segmentParameters[0] = segmentStartPoints[i].x;
				segmentParameters[1] = segmentStartPoints[i].y;
				segmentParameters[2] = params[i].x;
				segmentParameters[3] = params[i].y;
				ID id = model->CreatePrimitive(ot_segment, segmentParameters);
				segIDs[i] = id;
			}
			undo_redo->AddVersion(tfc_creation, segIDs);
			return segIDs;
		}
		}
		break;
	}
	case ev_mouseMove:
	{
		if (stateClick == oneClick)
		{
			if (params.GetSize() != segmentStartPoints.GetSize())
			{
				throw std::invalid_argument("Bad number of parameters");
			}
			imaginaryPoints.Clear();
			for (int i = 0; i < params.GetSize(); i++)
			{
				imaginaryPoints.PushBack(params[i]);
			}
		}
		return Array<ID>(0);
	}
	}
	return Array<ID>(0);
}

void CreatingSegment::DrawMode() {
	if (stateClick == oneClick)
	{
		view->SetColor(col_Red);
		for (int i = 0; i < segmentStartPoints.GetSize(); i++)
		{
			view->DrawPoint(segmentStartPoints[i]);
		}
		view->SetColor(col_Yellow);
		for (int i = 0; i < imaginaryPoints.GetSize(); i++)
		{
			view->DrawLine(segmentStartPoints[i], imaginaryPoints[i], points);
		}
	}
}

CreatingSegment::~CreatingSegment() {
	segmentStartPoints.Clear();
	imaginaryPoints.Clear();
}
#pragma endregion

#pragma region CreatingPoint
CreatingPoint::CreatingPoint(){}

CreatingPoint::~CreatingPoint(){}

Array<ID> CreatingPoint::HandleEvent(const Event ev, Array<Vector2>& params) {
	if (ev == ev_leftMouseDown) {
		Array<ID>pointIDs(params.GetSize());
		for (int i = 0; i < params.GetSize(); i++)
		{
			Array<double> pointParameters;
			pointParameters.PushBack(params[i].x);
			pointParameters.PushBack(params[i].y);
			ID id = model->CreatePrimitive(ot_point, pointParameters);
			pointIDs[i] = id;
		}
		undo_redo->AddVersion(tfc_creation, pointIDs);
		return pointIDs;
	}
	return Array<ID>(0);
}

void CreatingPoint::DrawMode() {}
#pragma endregion

#pragma region CreatingCircle
CreatingCircle::CreatingCircle() : centerPoints(0) {
	stateClick = noClick;
}

Array<ID> CreatingCircle::HandleEvent(const Event ev, Array<Vector2>& params) {
	if (ev == ev_leftMouseDown) {
		if (stateClick == noClick) {
			for (int i = 0; i < params.GetSize(); i++)
			{
				centerPoints.PushBack(params[i]);
			}
			stateClick = oneClick;
			return Array<ID>(0);
		}
		if (stateClick == oneClick) {
			if (params.GetSize() != centerPoints.GetSize())
			{
				throw std::invalid_argument("Bad number of parameters");
			}
			Array<ID>circleIDs(centerPoints.GetSize());
			for (int i = 0; i < params.GetSize(); i++)
			{
				Array<double> circleParameters(3);
				circleParameters[0] = centerPoints[i].x;
				circleParameters[1] = centerPoints[i].y;
				circleParameters[2] = (params[i] - centerPoints[i]).GetLength();
				ID id = model->CreatePrimitive(ot_circle, circleParameters);
				circleIDs[i] = id;
			}
			undo_redo->AddVersion(tfc_creation, circleIDs);
			return circleIDs;
		}
	}
	if (ev == ev_mouseMove)
	{
		if (stateClick == oneClick)
		{
			imaginaryPoints.Clear();
			for (int i = 0; i < params.GetSize(); i++)
			{
				imaginaryPoints.PushBack(params[i]);
			}
		}
		return Array<ID>(0);
	}
	
}

void CreatingCircle::DrawMode() {
	if (stateClick == oneClick)
	{
		view->SetColor(col_Red);
		for (int i = 0; i < centerPoints.GetSize(); i++)
		{
			view->DrawPoint(centerPoints[i]);
		}
		view->SetColor(col_Yellow);
		for (int i = 0; i < imaginaryPoints.GetSize(); i++)
		{
			view->DrawCircle(centerPoints[i], imaginaryPoints[i], points);
		}
	}
}

CreatingCircle::~CreatingCircle() {
	centerPoints.Clear();
	imaginaryPoints.Clear();
}
#pragma endregion

#pragma region CreatingArc

CreatingArc::CreatingArc() {
	stateClick = noClick;
}

Array<ID> CreatingArc::HandleEvent(const Event ev, Array<Vector2>& params) {
	if (ev == ev_leftMouseDown) {
		if (stateClick == noClick) {
			for (int i = 0; i < params.GetSize(); i++)
			{
				centerPoints.PushBack(params[i]);
			}
			stateClick = oneClick;
			return Array<ID>(0);
		}
		if (stateClick == oneClick) {
			if (params.GetSize() != centerPoints.GetSize())
			{
				throw std::invalid_argument("Bad number of parameters");
			}
			for (int i = 0; i < params.GetSize(); i++)
			{
				startPoints.PushBack(params[i]);
			}
			stateClick = twoClick;
			return Array<ID>(0);
		}
		if (stateClick == twoClick) {
			if (params.GetSize() != centerPoints.GetSize())
			{
				throw std::invalid_argument("Bad number of parameters");
			}
			Array<ID>arcIDs(centerPoints.GetSize());
			for (int i = 0; i < params.GetSize(); i++)
			{
				Array<double> arcParameters(5);
				arcParameters[0] = startPoints[i].x;
				arcParameters[1] = startPoints[i].y;
				double radius1 = (startPoints[i] - centerPoints[i]).GetLength();
				double radius2 = (params[i] - centerPoints[i]).GetLength();
				if (abs(radius2) > DBL_EPSILON) {
					params[i] = centerPoints[i] + (params[i] - centerPoints[i]) / radius2 * radius1;
				}
				else {
					params[i] = centerPoints[i] - (startPoints[i] - centerPoints[i]);
				}
				arcParameters[2] = params[i].x;
				arcParameters[3] = params[i].y;
				arcParameters[4] = Vector2::Angle(startPoints[i] - centerPoints[i], params[i] - centerPoints[i]);
				ID id = model->CreatePrimitive(ot_arc, arcParameters);
				arcIDs[i] = id;
			}
			undo_redo->AddVersion(tfc_creation, arcIDs);
			return arcIDs;
		}
	}
	if (ev == ev_mouseMove)
	{
		if (stateClick != noClick) {
			imaginaryPoints.Clear();
			for (int i = 0; i < params.GetSize(); i++)
			{
				imaginaryPoints.PushBack(params[i]);
			}
		}
		return Array<ID>(0);
	}
	return Array<ID>(0);
}

void CreatingArc::DrawMode() {
	if (stateClick == oneClick)
	{
		view->SetColor(col_Red);
		for (int i = 0; i < centerPoints.GetSize(); i++)
		{
			view->DrawPoint(centerPoints[i]);
		}
		view->SetColor(col_Bisque);
		for (int i = 0; i < imaginaryPoints.GetSize(); i++)
		{
			view->DrawCircle(centerPoints[i], imaginaryPoints[i], points);
		}
	}
	if (stateClick == twoClick)
	{
		view->SetColor(col_Red);
		for (int i = 0; i < centerPoints.GetSize(); i++)
		{
			view->DrawPoint(centerPoints[i]);
		}

		view->SetColor(col_Bisque);
		for (int i = 0; i < startPoints.GetSize(); i++)
		{
			view->DrawCircle(centerPoints[i], startPoints[i], points);
		}

		view->SetColor(col_Red);
		for (int i = 0; i < startPoints.GetSize(); i++)
		{
			view->DrawPoint(startPoints[i]);
		}

		view->SetColor(col_Bisque);
		for (int i = 0; i < imaginaryPoints.GetSize(); i++)
		{
			view->DrawArc(centerPoints[i], startPoints[i], imaginaryPoints[i], line);
		}
	}
}

CreatingArc::~CreatingArc() {
}
#pragma endregion