//---------------------------------------------------------------------------

#ifndef CircleH
#define CircleH

#include "Figure.h"

class Circle : public Figure
{
	int x1, y1, x2, y2;
	float S, P;
	int X, Y;
	public:
	Circle(){}  //конструктор по умолчанию
	Circle(int, int, int, int); //конструктор
	~Circle(){}   //деструктор
	void Set(int, int, int, int);
	void show(TCanvas *Canvas);
	float Area();
	float Perimeter();
	int XCentMass();
	int YCentMass();
	void hide(TCanvas *Canvas);
	void change(float, int &, int &, int &, int &);  //изменение радиуса
};

#endif
