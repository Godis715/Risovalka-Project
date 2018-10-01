#include "ViewHeaders.h"

//DisplayWidjet
DisplayWidjet::DisplayWidjet() {}
DisplayWidjet::~DisplayWidjet() {}
//______________

Inventory::Inventory()
{
	lastEvent = ev_ctrlUp;

	lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);
}

Inventory* Inventory::GetInstance()
{
	if (instance == nullptr) {
		instance = new Inventory();
	}
	return instance;
}

Inventory* Inventory::instance = nullptr;


