#include "viewFLTK.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v{ 1, 3 , 2, 3, 3,  5, 5, 6};
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	sort(v.begin(), v.end());
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl << endl;

	vector<int> v1{ 8, 2, 9 , 4, 5, 6 };
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	sort(v1.begin(), v1.end());
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	
	//ostreambuf_iterator<int> outIt();
	vector<int> out(10);
	set_difference(v.begin(), v.end(), v1.begin(), v1.end(), out.begin());
	for (size_t i = 0; i < out.size(); i++)
	{
		cout << out[i] << " ";
	}
	//IView * view = new ViewFLTK();
	//return view->Run();
	system("pause");
	return 0;
}