#include "ViewHeaders.h"

Inventory::Inventory()
{
	Event lastEvent = ev_ctrlUp;

	Fl_Cursor* lastCursor = new Fl_Cursor(FL_CURSOR_DEFAULT);

	Fl_Widget* currentWindget;
}

Inventory* Inventory::GetInstance()
{
	if (instance == nullptr) {
		instance = new Inventory();
	}
	return instance;
}

Inventory* Inventory::instance = nullptr;
