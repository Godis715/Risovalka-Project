#include "View.h"
#include <ctime>

Array<Model> func() {
	Array<Model> k(500);
	return k;
}

int main()
{
	IView* view = new View;
	view->Run();

	return 0;
}