#include "ViewDisplay.h"

#pragma region DisplayParams
void DisplayParams::DisplayPoint(const Array<string>& params)
{
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
	inputs[0]->value(str_ch(params[0]));


	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
	inputs[1]->value(str_ch(params[1]));
}

void DisplayParams::DisplaySegment(const Array<string>& params)
{
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x1"));
	inputs[0]->value(str_ch(params[0]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y1"));
	inputs[1]->value(str_ch(params[1]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "x2"));
	inputs[2]->value(str_ch(params[2]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 100, 50, 30, "y2"));
	inputs[3]->value(str_ch(params[3]));
}

void DisplayParams::DisplayArc(const Array<string>& params)
{
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x1"));
	inputs[0]->value(str_ch(params[0]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y1"));
	inputs[1]->value(str_ch(params[1]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "x2"));
	inputs[2]->value(str_ch(params[2]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 100, 50, 30, "y2"));
	inputs[3]->value(str_ch(params[3]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 130, 50, 30, "an"));
	inputs[4]->value(str_ch(params[4]));
}

void DisplayParams::DisplayCircle(const Array<string>& params)
{
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
	inputs[0]->value(str_ch(params[0]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
	inputs[1]->value(str_ch(params[1]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "r"));
	inputs[2]->value(str_ch(params[2]));
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

void DisplayParams::cl_Close(Fl_Widget* _b_close, void*) {
	Array<double> params(0);
	Presenter::Set_event(ev_delete_widjet, params);
}

void DisplayParams::cl_req(Fl_Widget* ob_req, void*) {
	throw std::exception("ssdfgfd");
}

void DisplayParams::Inizializatoin(const Array<string>& params, const Array<string>& nameReqs)
{
	switch (params.GetSize())
	{
	case 2:
	{
		sizeY = 80;
		break;
	}
	case 4:
	{
		sizeY = 140;
		break;
	}
	case 5:
	{
		sizeY = 170;
		break;
	}
	case 3:
	{
		sizeY = 110;
		break;
	}
	default:
		break;
	}
	group = new Fl_Group(coordX, coordY, sizeX, sizeY);
	{
		switch (params.GetSize())
		{
		case 2: {
			DisplayPoint(params);
			break;
		}
		case 4: {
			DisplaySegment(params);
			break;
		}
		case 5: {
			DisplayArc(params);
			break;
		}
		case 3: {
			DisplayCircle(params);
			break;
		}
		default:
			break;
		}
		b_OK = new Fl_Button(coordX + 80, coordY + sizeY - 30, 30, 20, "OK");
		b_OK->color(FL_WHITE);
		b_OK->callback(cl_OK);

		b_close = new Fl_Button(coordX + 120, coordY + sizeY - 30, 30, 20, "X");
		b_close->color(FL_WHITE);
		b_close->callback(cl_Close);

		{
			i_req = new Fl_Menu_Item[nameReqs.GetSize() + 1];
			for (int i = 0; i < nameReqs.GetSize(); ++i) {
				const char* nameIt = str_ch(nameReqs[i]);
				i_req[i] = { nameIt };
			}
			i_req[nameReqs.GetSize()] = { 0 };
			b_req = new  Fl_Menu_Button(coordX + 80, coordY + 10, 50, 30, "Req");
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
	Clear();
}

void DisplayParams::Clear() {
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
#pragma endregion

#pragma region RequirementInput
RequirementInput::RequirementInput()
{
	textBuffer = new Fl_Float_Input(1010, 60, 100, 30);
	textBuffer->when(FL_WHEN_ENTER_KEY);
	textBuffer->callback(cl_Input);
}

RequirementInput::~RequirementInput()
{
	delete textBuffer;
}

void RequirementInput::cl_Input(Fl_Widget* o, void*) {

	fl_cursor(FL_CURSOR_DEFAULT);

	Array<double> params(1);
	string numbers = ((Fl_Float_Input*)o)->value();
	((Fl_Float_Input*)o)->value("");
	params[0] = Parse(numbers);
	Presenter::Set_event(ev_input, params);
}
#pragma endregion




