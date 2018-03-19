#include <iostream>
#include <clocale>
#include <string>
#include "List.h"

/*#include "list_util.h"
#include <ctime>

#include "Rational.h"
*/
using namespace std;
#include "IDGenerator.h"

class Person{
public:
    Person(const string&n):_name(n){}
    virtual string hello()const{return _name + " is my name";}
private:
    string _name;
};

class Student: public Person{
public:
     Student():Person("Student "){}
     string hello()const{ return Person::hello() + " - don't call me brick!!!";}
     void doHomework(){cout << "Trying...";};
};


int main()
{
    List<Person*> personList;
    Person p("John");

    personList.addElementAfterTail(&p);

    Student s;

    personList.addElementAfterTail(&s);

    List<Person*>::Marker *m = personList.createMarker();
    do{
        cout << m->getCurrent()->hello() << endl;
    }
    while (m->moveNext());

    cout << "================" << endl;
    cout << p.hello() << endl;
    cout << s.hello() << endl;




    /*

    IDGenerator *idgen = IDGenerator::getInstance();

cout << idgen->generateID() << endl;

cout << idgen->generateID() << endl;
    //Point p1(10,20,);
    /*Point p2(20,240,idgen.generateID());

    IDGenerator idgen1;
    Point p3(10,20,idgen1.generateID());





    Rational r1(2,3);
    Rational r2(5,4);

    //Rational r3 = r1+r2;
    Rational r3 = r1.operator+(r2);

    r3++;


	srand(time(nullptr));
	List<int> list;
	try {
		std::setlocale(LC_ALL, "Russian");
		for (int i = 0; i < 100; ++i) {
			list.addElementAfterTail(rand()%1000);
		}
		printList(list);
	}
	catch (std::exception e) {
		std::cout << "baaad";
	}
	std::cout << std::endl;
	BublesSort<int>(list);
	printList<int>(list);
	*/
	system("pause");
	return 0;
}
