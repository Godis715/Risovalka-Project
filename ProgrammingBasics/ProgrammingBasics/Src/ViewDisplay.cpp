#include "ViewDisplay.h"

#pragma region DisplayParamsPrim
void DisplayParamsPrim::DisplayPoint(const Array<string>& params)
{
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
	inputs[0]->value(str_ch(params[0]));


	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
	inputs[1]->value(str_ch(params[1]));
}

void DisplayParamsPrim::DisplaySegment(const Array<string>& params)
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

void DisplayParamsPrim::DisplayArc(const Array<string>& params)
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

void DisplayParamsPrim::DisplayCircle(const Array<string>& params)
{
	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10, 50, 30, "x"));
	inputs[0]->value(str_ch(params[0]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 40, 50, 30, "y"));
	inputs[1]->value(str_ch(params[1]));

	inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 70, 50, 30, "r"));
	inputs[2]->value(str_ch(params[2]));
}

void DisplayParamsPrim::cl_OK(Fl_Widget* o, void*)
{
	Array<double> params;
	for (int i = 0; i < inputs.GetSize(); i++)
	{
		params.PushBack(Parse(inputs[i]->value()));
	}
	Presenter::Set_event(ev_change_Prim, params);
}

void DisplayParamsPrim::cl_Close(Fl_Widget* _b_close, void*) {
	Array<double> params(0);
	Presenter::Set_event(ev_delete_display_Prim, params);
}

void DisplayParamsPrim::cl_req(Fl_Widget* ob_req, void*) {
	Array<double> params;
	params.PushBack(((Fl_Menu_Button*)ob_req)->value());
	Presenter::Set_event(ev_click_Req, params);
}

void DisplayParamsPrim::Inizializatoin(const Array<string>& params, const Array<string>& nameReqs)
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
			b_req->callback(cl_req);
			b_req->clear_visible_focus();
			b_req->color(FL_WHITE);
		}
		group->color(FL_YELLOW);
		group->box(FL_UP_BOX);
		group->end();
	}

}

void DisplayParamsPrim::GetParamDisplay(Array<int>& paramDisp)
{
	paramDisp.Clear();
	paramDisp.PushBack(coordX);
	paramDisp.PushBack(coordY);
	paramDisp.PushBack(sizeX);
	paramDisp.PushBack(sizeY);
}

DisplayParamsPrim::DisplayParamsPrim(){}

DisplayParamsPrim::~DisplayParamsPrim()
{
	Clear();
}

void DisplayParamsPrim::Clear() {
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

Array<Fl_Float_Input*> DisplayParamsPrim::inputs;
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

#pragma region DisplayParamsReq
void DisplayParamsReq::cl_OK(Fl_Widget* _b_ok, void*)
{
	Array<double> params;
	for (int i = 0; i < inputs.GetSize(); i++)
	{
		params.PushBack(Parse(inputs[i]->value()));
	}
	Presenter::Set_event(ev_change_Req, params);
}

void DisplayParamsReq::cl_Close(Fl_Widget* _b_close, void*) {
	Array<double> params(0);
	Presenter::Set_event(ev_delete_display_Req, params);
}

void DisplayParamsReq::cl_Delete(Fl_Widget* _b_delete, void*)
{
	Array<double> params(0);
	Presenter::Set_event(ev_delete_Req, params);
}

void DisplayParamsReq::CreateInputs(const Array<string>& params)
{
	for (int i = 0; i < params.GetSize(); i++)
	{
		string name = "p" + std::to_string(i);
		inputs.PushBack(new Fl_Float_Input(coordX + 20, coordY + 10 + 30 * i, 50, 30, str_ch(name)));
		inputs[i]->value(str_ch(params[i]));
	}
}

void DisplayParamsReq::Inizializatoin(const Array<string>& params, const string nameReq)
{
	switch (params.GetSize())
	{
	case 0:
	{
		sizeY = 40;
		break;
	}
	case 1:
	{
		sizeY = 80;
		break;
	}
	case 2:
	{
		sizeY = 110;
		break;
	}
	default:
		break;
	}		
	group = new Fl_Group(coordX, coordY, sizeX, sizeY, str_ch(nameReq));
	{
		CreateInputs(params);

		if (params.GetSize() > 0)
		{
			b_OK = new Fl_Button(coordX + 20, coordY + sizeY - 30, 30, 20, "OK");
			b_OK->color(FL_WHITE);
			b_OK->callback(cl_OK);
		}
		if (params.GetSize() == 0)
		{
			b_delete = new Fl_Button(coordX + 10, coordY + sizeY - 30, 30, 20, "Del");
		}
		else
		{
			b_delete = new Fl_Button(coordX + 80, coordY + sizeY - 30, 30, 20, "Del");
		}
		b_delete->color(FL_WHITE);
		b_delete->callback(cl_Delete);

		b_close = new Fl_Button(coordX + sizeX - 40, coordY + 10, 30, 20, "X");
		b_close->color(FL_WHITE);
		b_close->callback(cl_Close);

		group->color(FL_GREEN);
		group->box(FL_UP_BOX);
		group->end();
	}
}

DisplayParamsReq::DisplayParamsReq(int _coordX, int _coordY) : coordX(_coordX), coordY(_coordY){}

DisplayParamsReq::~DisplayParamsReq()
{
	Clear();
}

void DisplayParamsReq::Clear() {
	delete b_OK;
	delete b_delete;
	delete b_close;
	for (int i = 0; i < inputs.GetSize(); i++)
	{
		delete inputs[i];
	}
	inputs.Clear();
	delete group;
}

Array<Fl_Float_Input*> DisplayParamsReq::inputs;
#pragma endregion


