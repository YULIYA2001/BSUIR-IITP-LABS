//---------------------------------------------------------------------------

#ifndef RectH
#define RectH

#include "Figure.h"

class  Rectan : public Figure
{
	int x1, y1, x2, y2;
	int x3, x4, y3, y4;
	float S, P;
	int X, Y;
	public:
	Rectan(){}  //конструктор по умолчанию
	Rectan(int, int, int, int); //конструктор
	~Rectan(){}   //деструктор
	void Set(int, int, int, int);
	void show(TCanvas *Canvas);
	float Area();
	float Perimeter();
	int XCentMass();
	int YCentMass();
	void hide(TCanvas *Canvas);
	void Rotation(int&,int&,int&,int&,int&,int&,int&,int&); //вращение
	void SetForRotation(int, int, int, int, int, int, int, int);
};

#endif
