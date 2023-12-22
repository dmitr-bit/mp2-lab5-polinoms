#include <iostream>
#include "TList.h"
#include "TPolinom.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");
	string st;
	st = "3x^5y^2z^4-3x^7y^2z^4+3x^2y^2z^4";
	TPolinom b(st);
	cout << b.ToString() << endl << "+" << endl;
	st = "4x^5y^2z^4+3x^9y^9z^9";
	TPolinom a(st);
	cout << a.ToString() << endl << "="<<endl;
	TPolinom c(st);
	c = a + b;
	cout << c.ToString();



}