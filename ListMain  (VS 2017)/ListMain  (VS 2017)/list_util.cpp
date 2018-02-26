#include "list_util.h"
#include <iostream>

void printList(List&l){
	l.moveHead();
	do{
		try
		{
			std::cout << l.getCurrent();
		}
		catch(std::out_of_range)
		{
			std::cout << "Список пуст\n";
		}
	}while ( !l.moveNext() );
}