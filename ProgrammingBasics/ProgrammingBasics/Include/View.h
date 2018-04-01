#pragma once

#include "Presenter.h"
#include "IView.h"
#include<windows.h>


class View : public IView
{
private:
	Presenter* presenter;

public:

	/*View() : presenter(new Presenter(this))
	{

	}*/
};

