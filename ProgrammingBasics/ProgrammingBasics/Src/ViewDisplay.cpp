#include "ViewDisplay.h"

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

//DisplayParams
bool DisplayParams::DisplayPoint(const Array<double>& params)
{
	if (params.GetSize() != 2) return false; //исключение
	int digLength = 0;
	const char* dig;

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
	dig = ReverseParse(params[0], digLength);
	inputs[0]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
	dig = ReverseParse(params[1], digLength);
	inputs[1]->value(dig, digLength);
}

bool DisplayParams::DisplaySegment(const Array<double>& params)
{
	if (params.GetSize() != 4) return false; //исключение
	int digLength = 0;
	const char* dig;

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x1"));
	dig = ReverseParse(params[0], digLength);
	inputs[0]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y1"));
	dig = ReverseParse(params[1], digLength);
	inputs[1]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "x2"));
	dig = ReverseParse(params[2], digLength);
	inputs[2]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 100, 50, 30, "y2"));
	dig = ReverseParse(params[3], digLength);
	inputs[3]->value(dig, digLength);
}

bool DisplayParams::DisplayArc(const Array<double>& params)
{
	if (params.GetSize() != 6) return false; //исключение
	int digLength = 0;
	const char* dig;

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x1"));
	dig = ReverseParse(params[2], digLength);
	inputs[0]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y1"));
	dig = ReverseParse(params[3], digLength);
	inputs[1]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "x2"));
	dig = ReverseParse(params[4], digLength);
	inputs[2]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 100, 50, 30, "y2"));
	dig = ReverseParse(params[5], digLength);
	inputs[3]->value(dig, digLength);

	Vector2 vector1 = Vector2(params[2], params[3]) - Vector2(params[0], params[1]);
	Vector2 vector2 = Vector2(params[4], params[5]) - Vector2(params[0], params[1]);
	double angle = (Vector2::Angle(vector1, vector2) * 180) / PI;
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 130, 50, 30, "an"));
	dig = ReverseParse(angle, digLength);
	inputs[4]->value(dig, digLength);
}

bool DisplayParams::DisplayCircle(const Array<double>& params)
{
	if (params.GetSize() != 3) return false; //исключение
	int digLength = 0;
	const char* dig;

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
	dig = ReverseParse(params[0], digLength);
	inputs[0]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
	dig = ReverseParse(params[1], digLength);
	inputs[1]->value(dig, digLength);

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "r"));
	dig = ReverseParse(params[2], digLength);
	inputs[2]->value(dig, digLength);
}

void DisplayParams::cl_OK(Fl_Widget* o, void*)
{
	Array<double> params;
	for (int i = 0; i < inputs.GetSize(); i++)
	{
		params.PushBack(Parse(inputs[i]->value()));
	}
	Presenter::Set_event(ev_change_Prim, params);
}

void DisplayParams::Inizializatoin(const object_type _type, const Array<double>& params,
	const Array<string>& nameReqs, const Array<Array<double>>& reqParams)
{
	switch (_type)
	{
	case ot_point:
		sizeY = 140;
		break;
	case ot_segment:
		sizeY = 200;
		break;
	case ot_arc:
		sizeY = 230;
		break;
	case ot_circle:
		sizeY = 170;
		break;
	default:
		break;
	}
	group = new Fl_Group(coordX, coordY, sizeX, sizeY);
	{
		switch (_type)
		{
		case ot_point: {
			DisplayPoint(params);
			break;
		}
		case ot_segment: {
			DisplaySegment(params);
			break;
		}
		case ot_arc: {
			DisplayArc(params);
			break;
		}
		case ot_circle: {
			DisplayCircle(params);
			break;
		}
		default:
			break;
		}
		type = _type;
		b_OK = new Fl_Button(coordX + 10, coordY + sizeY - 30, 30, 20, "OK");
		b_OK->color(FL_WHITE);
		b_OK->callback(cl_OK);
		{
			i_req = new Fl_Menu_Item[nameReqs.GetSize() + 1];
			for (int i = 0; i < nameReqs.GetSize(); ++i) {
				char* nameIt = new char[nameReqs[i].size() + 1];
				for (int j = 0; j < nameReqs[i].size(); j++)
				{
					nameIt[j] = nameReqs[i][j];
				}
				nameIt[nameReqs[i].size()] = '\0';
				i_req[i] = { nameIt };
				//delete[] nameIt;
			}
			i_req[nameReqs.GetSize()] = { 0 };
			b_req = new  Fl_Menu_Button(coordX + 90, coordY + 10, 50, 30, "Req");
			b_req->menu(i_req);
			b_req->callback(cl_OK);
			b_req->clear_visible_focus();
			b_req->color(FL_WHITE);
		}
		group->color(FL_YELLOW);
		group->box(FL_UP_BOX);
		group->end();
	}

}

DisplayParams::DisplayParams(){}

DisplayParams::~DisplayParams()
{
	delete b_OK;
	delete b_close;
	delete b_req;
	for (int i = 0; i < inputs.GetSize(); i++)
	{
		delete inputs[i];
	}
	inputs.Clear();
	delete group;
}

Array<Fl_Float_Input*> DisplayParams::inputs;
//______________

//RequirementInput
RequirementInput::RequirementInput()
{
	textBuffer = new Fl_Float_Input(1010, 60, 100, 30);
	textBuffer->when(FL_WHEN_ENTER_KEY);
	textBuffer->callback(cl_Input);
}

RequirementInput::~RequirementInput(){}

void RequirementInput::cl_Input(Fl_Widget* o, void*) {

	fl_cursor(FL_CURSOR_DEFAULT);

	Array<double> params(1);
	string numbers = ((Fl_Float_Input*)o)->value();
	((Fl_Float_Input*)o)->value("");
	params[0] = Parse(numbers);
	Presenter::Set_event(ev_input, params);
}
//______________



