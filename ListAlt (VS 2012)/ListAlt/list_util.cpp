#include "list_util.h"
#include <iostream>

void printList(List&list){
	List::Marker marker(&list);
	do{
		try
		{
			std::cout << marker.getCurrent()->getValue();
		}
		catch(std::out_of_range)
		{
			std::cout << "Список пуст\n";
		}
	}while ( !marker.moveNext() );
}