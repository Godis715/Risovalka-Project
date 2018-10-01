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
	case ev_createPoint: {
		return new CreatingPoint();
	}
	case ev_createArc: {
		return new CreatingArc();
	}
	case ev_createSegment: {
		return new CreatingSegment();
	}
	case ev_createCircle: {
		return new CreatingCircle();
	}
	case ev_mouseMove:
		return nullptr;
	case ev_leftMouseUp:
		return nullptr;
	case ev_ctrlDown:
		return nullptr;
	case ev_ctrlUp:
		return nullptr;
	default:
		return new Selection();
	}
}

Mode::Mode() {
	model = Model::GetInstance();
	modelNew = ModelNew::GetInstance();
	view = Presenter::GetView();
}
#pragma endregion

#pragma region CreatingSegment
CreatingSegment::CreatingSegment() : segmentParameters(4) {
	state = noClick;
}

Mode* CreatingSegment::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		// if it were no clicks
		// then create one point and change the state
		// to one click
		if (state == noClick) {

			segmentParameters[0] = params[0];
			segmentParameters[1] = params[1];

			state = oneClick;
			//for draw mode
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}

		// if it was one click
		// then create a segment
		// and turn to single selection mode
		// with selected segment
		if (state == oneClick) {

			segmentParameters[2] = params[0];
			segmentParameters[3] = params[1];

			ID id = modelNew->CreatePrimitive(ot_segment, segmentParameters);
			model->CreateObject(ot_segment, segmentParameters, id); // $$$

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}
	if (ev == ev_mouseMove)
	{
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}

		if (state == noClick) {
			return nullptr;
		}

		if (state == oneClick) {
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
	}
	return UnexpectedEvent(ev);
}

void CreatingSegment::DrawMode() {
	if (state == oneClick)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(segmentParameters[0], segmentParameters[1]));
		view->SetColor(yellow);
		view->DrawLine(Vector2(segmentParameters[0], segmentParameters[1]), infoMode, points);
	}
}

CreatingSegment::~CreatingSegment() {
	segmentParameters.Clear();
	state = noClick;
}
#pragma endregion

#pragma region CreatingPoint
Mode* CreatingPoint::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}

		ID id = modelNew->CreatePrimitive(ot_point, params);
		model->CreateObject(ot_point, params, id); // $$$

		Array<ID> selectedObjects(1);
		selectedObjects[0] = id;
		return new Selection(selectedObjects);
	}
	return UnexpectedEvent(ev);
}

void CreatingPoint::DrawMode() {
}
#pragma endregion

#pragma region CreatingCircle
CreatingCircle::CreatingCircle() : CircleParameters(3) {
	state = noClick;
}

Mode* CreatingCircle::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		// if it were no clicks
		// then create one point and change the state
		// to one click
		if (state == noClick) {

			CircleParameters[0] = params[0];
			CircleParameters[1] = params[1];

			state = oneClick;
			//for draw mode
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
		// if it was one click
		// then create a circle
		// and turn to single selection mode
		// with selected circle
		if (state == oneClick) {
			CircleParameters[2] = (Vector2(params[0], params[1]) - Vector2(CircleParameters[0], CircleParameters[1])).GetLength();
			
			ID id = modelNew->CreatePrimitive(ot_circle, CircleParameters);
			model->CreateObject(ot_circle, CircleParameters, id); // $$$

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}
	if (ev == ev_mouseMove)
	{
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		if (state == noClick) {
			return nullptr;
		}

		if (state == oneClick) {
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
	}
	return this->UnexpectedEvent(ev);
}

void CreatingCircle::DrawMode() {
	if (state == oneClick)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(CircleParameters[0], CircleParameters[1]));
		view->SetColor(yellow);
		view->DrawCircle(Vector2(CircleParameters[0], CircleParameters[1]), infoMode, points);
	}
}

CreatingCircle::~CreatingCircle() {
	CircleParameters.Clear();
}
#pragma endregion

#pragma region CreatingArc
CreatingArc::CreatingArc() : arcParameters(6) {
	state = noClick;
}

Mode* CreatingArc::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_leftMouseDown) {
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		// if it were no clicks
		// then create one point and change the state
		// to one click
		if (state == noClick) {

			arcParameters[0] = params[0];
			arcParameters[1] = params[1];

			state = oneClick;
			//for draw mode
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
		// if it were one clicks
		// then create one point and change the state
		// to two click
		if (state == oneClick) {

			arcParameters[2] = params[0];
			arcParameters[3] = params[1];

			state = twoClick;
			return nullptr;
		}
		// if it was two click
		// then create a arc
		// and turn to single selection mode
		// with selected arc
		if (state == twoClick) {

			arcParameters[4] = params[0];
			arcParameters[5] = params[1];

			ID id = modelNew->CreatePrimitive(ot_arc, arcParameters);
			model->CreateObject(ot_arc, arcParameters, id); // $$$

			Array<ID> selectedObjects(1);
			selectedObjects[0] = id;
			return new Selection(selectedObjects);
		}
	}
	if (ev == ev_mouseMove)
	{
		if (params.GetSize() != 2) {
            throw std::invalid_argument("Bad number of parameters");
		}
		if (state == noClick) {
			return nullptr;
		}

		if (state == oneClick || state == twoClick) {
			infoMode.x = params[0];
			infoMode.y = params[1];
			return nullptr;
		}
	}
	return this->UnexpectedEvent(ev);
}

void CreatingArc::DrawMode() {
	if (state == oneClick)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(arcParameters[0], arcParameters[1]));

		view->SetColor(yellow);
		view->DrawCircle(Vector2(arcParameters[0], arcParameters[1]), infoMode, points);
	}
	if (state == twoClick)
	{
		view->SetColor(red);
		view->DrawPoint(Vector2(arcParameters[0], arcParameters[1]));

		view->SetColor(yellow);
		view->DrawCircle(Vector2(arcParameters[0], arcParameters[1]), Vector2(arcParameters[2], arcParameters[3]), points);
		
		view->SetColor(red);
		view->DrawPoint(Vector2(arcParameters[2], arcParameters[3]));
		
		view->SetColor(yellow);
		view->DrawArc(Vector2(arcParameters[0], arcParameters[1]), Vector2(arcParameters[2], arcParameters[3]), infoMode, line);
	}
}

CreatingArc::~CreatingArc() {
	arcParameters.Clear();
}
#pragma endregion

#pragma region Changing_Properties
ChangingProperties::ChangingProperties() : Mode()
{

}

ChangingProperties::ChangingProperties(const ID _selObject) : Mode(), selectedObject(_selObject)
{
	object_type typePrim;
	model->GetObjType(selectedObject, typePrim);

	Array<double> params;
	model->GetObjParam(selectedObject, params);

	Array<string> paramsString;
	if (typePrim == ot_arc){
		paramsString = Array<string>(params.GetSize() - 1);
		Vector2 vector1 = Vector2(params[2], params[3]) - Vector2(params[0], params[1]);
		Vector2 vector2 = Vector2(params[4], params[5]) - Vector2(params[0], params[1]);
		double angle = (Vector2::Angle(vector1, vector2) * 180) / PI;
		for (int i = 2; i < params.GetSize(); ++i) {
			paramsString[i - 2] = ReverseParse(params[i]);
		}
		paramsString[params.GetSize() - 2] = ReverseParse(angle);
	}
	else {
		paramsString = Array<string>(params.GetSize());
		for (int i = 0; i < params.GetSize(); ++i) {
			paramsString[i] = ReverseParse(params[i]);
		}
	}

	model->GetRequirementsByID(selectedObject, reqIDs);

	Array<string> nameReqs;
	for (int i = 0; i < reqIDs.GetSize(); i++)
	{
		object_type typeReq;
		model->GetObjType(reqIDs[i], typeReq);
		nameReqs.PushBack(objTypeToString(typeReq) + '#' + reqIDs[i].GetHash());
	}

	widjet = static_cast<IDisplayParam*>(view->GetWidjet(displayParam));

	widjet->SetParam(paramsString, nameReqs);
}

ChangingProperties::~ChangingProperties()
{
	if (isNew) {
		delete widjet;
	}
}

Mode* ChangingProperties::HandleEvent(const Event e, Array<double>& params)
{
	if (e == ev_change_Prim)
	{
		modelNew->ChangeObject(selectedObject, params);
		model->ChangePrimitive(selectedObject, params);
		return new Selection();
	}
	if (e == ev_rightMouseDown)
	{
		ID obj = modelNew->GetObjectByClick(params[0], params[1]);
		bool isFound = Presenter::GetObject(params[0], params[1], obj);
		if (isFound)
		{
			isNew = false;
			delete widjet;
			return new ChangingProperties(obj);
		}
		return nullptr;
	}
	
	return UnexpectedEvent(e);
}

void ChangingProperties::DrawMode()
{
	Array<ID> selectedObjects;
	selectedObjects.PushBack(selectedObject);
	Presenter::DrawSelectedObjects(selectedObjects, orange);
}
#pragma endregion

#pragma region Selection
Selection::Selection(Array<ID> _selObjects) : Mode(), selectedObjects(_selObjects) {
	if (selectedObjects.GetSize() == 0) {
		selectedObjects = Array<ID>(1);
	}
	state = single_selection;
}

Selection::Selection() : Mode(), selectedObjects(1) {
	state = single_selection;
}

Selection::~Selection() {
	selectedObjects.Clear();
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

Mode* Selection::HandleEvent(const Event e, Array<double>& params) {
	if (e == ev_rightMouseDown)
	{
		selectedObjects.Clear();
		ID obj = modelNew->GetObjectByClick(params[0], params[1]);
		bool isFound = Presenter::GetObject(params[0], params[1], obj);
		if (isFound)
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

		ID obj = modelNew->GetObjectByClick(params[0], params[1]);
		bool isFound = Presenter::GetObject(params[0], params[1], obj);
		if (isFound) {
			if (state == single_selection) {
				selectedObjects.Clear();
				selectedObjects.PushBack(obj);
				return nullptr;
			}

			if (state == poly_selection) {
				AddObject(obj);
				return nullptr;
			}
		}
		else {
			if (state != poly_selection)
			{
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
		selectedObjects = modelNew->GetObjectsByArea(infoArea1.x, infoArea1.y, infoArea2.x, infoArea2.y);
		//Presenter::GetObjectsOnArea(infoArea1.x, infoArea1.y, infoArea2.x, infoArea2.y, selectedObjects);
		Array<object_type> temp;
		model->GetObjectsOnArea(infoArea1.x, infoArea1.y, infoArea2.x, infoArea2.y, selectedObjects, temp);
		return nullptr;
	}
	if (e == ev_leftMouseUp)
	{
		if (lastEvent == ev_mouseMove)
		{
			state = single_selection;
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
		model->DeletePrimitives(selectedObjects);
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

		modelNew->CreateRequirement(ot_equalSegmentLen, selectedObjects, param);
		ID id;
		model->CreateRequirementByID(ot_equalSegmentLen, selectedObjects, param, id);
		return nullptr;
	}
	case ev_req_on_one_hand: {
		Array<double>param(0);

		modelNew->CreateRequirement(ot_pointsOnTheOneHand, selectedObjects, param);
		ID id;
		model->CreateRequirementByID(ot_pointsOnTheOneHand, selectedObjects, param, id);
		return nullptr;
	}
	default:
		return UnexpectedEvent(e);
	}
}

void Selection::DrawMode()
{
	Presenter::DrawSelectedObjects(selectedObjects, green);

	if (state == area_selection)
	{
		Vector2 point1(infoArea2.x, infoArea1.y);
		Vector2 point2(infoArea1.x, infoArea2.y);

		view->SetColor(blue);
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
		status = scale;
		break;
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
			posEnd.x = params[0];
			posEnd.y = params[1];
			modelNew->Move(selectedObjects, posEnd - posStart);
			model->Move(selectedObjects, posEnd - posStart);
			posStart = posEnd;
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
			modelNew->Scale(selectedObjects, coef);
			model->Scale(selectedObjects, coef);
			return nullptr;
		}
	}
	if (e == ev_escape)
	{
		return new Selection(selectedObjects);
	}
	if (e == ev_scaleObjects)
	{
		return new Redaction(selectedObjects, ev_scaleObjects);
	}
	if (e == ev_moveObjects)
	{
		return new Redaction(selectedObjects, ev_moveObjects);
	}
	if (e == ev_del)
	{
		modelNew->DeleteObjects(selectedObjects);
		model->DeletePrimitives(selectedObjects);
		return new Selection();
	}
	return UnexpectedEvent(e);
}

void Redaction::DrawMode() {
	Presenter::DrawSelectedObjects(selectedObjects, green);
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
CreateRequirementWithParam::CreateRequirementWithParam(Array<ID> _selecObj, Event _ev) : selectedPrim(_selecObj) {
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

CreateRequirementWithParam::CreateRequirementWithParam() { }

CreateRequirementWithParam::~CreateRequirementWithParam() {
	
}

Mode* CreateRequirementWithParam::HandleEvent(const Event ev, Array<double>& params) {
	if (ev == ev_input)
	{
		if (params.GetSize() != 1) {
            throw std::invalid_argument("Bad number of parameters");
		}

		modelNew->CreateRequirement(typeRequirement, selectedPrim, params);
		//
		ID d;
		model->CreateRequirementByID(typeRequirement, selectedPrim, params, d);
		//
		return new Selection(selectedPrim);

	}
	if (ev == ev_escape)
	{
		return new Selection(selectedPrim);
	}

	return UnexpectedEvent(ev);
}

void CreateRequirementWithParam::DrawMode() {
	Presenter::DrawSelectedObjects(selectedPrim, green);
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
	Presenter::DrawSelectedObjects(selectedPrim, green);
}
#pragma endregion