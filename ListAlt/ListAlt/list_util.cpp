#include "list_util.h"
#include <iostream>

void printList(List&l){
	l.moveHead();
	do{
	std::cout << l.getCurrent();	
	}while ( !l.moveNext() );
}