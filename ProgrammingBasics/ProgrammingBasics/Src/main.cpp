#include "View.h"
#include <ctime>

int main()
{
	IView* view = new View;
	view->Run();
	system("pause");
	return 0;
}