//---------------------------------------------------------------------------

#ifndef TriangleH
#define TriangleH

#include "Figure.h"

class  Triangle : public Figure
{
	int x1,y1,x2,y2;
    int x3,y3;
	float S, P, helpSide;
	int X, Y;
	public:
	Triangle(){}  //����������� �� ���������
	Triangle(int, int, int, int); //�����������
	~Triangle(){}   //����������
    void Set(int, int, int, int);
	void show(TCanvas *Canvas);
	float Area();
	float Perimeter();
	int XCentMass();
	int YCentMass();
	void hide(TCanvas *Canvas);
	void change(float, int &, int &, int &, int &);  //��������� ����� �������
	void Rotation(int &x1, int &y1, int &x2, int &y2); //��������
	void Rotation(int&,int&,int&,int&,int&,int&); //��������
	void SetForRotation(int, int, int, int, int, int);
};

#endif
