//---------------------------------------------------------------------------

#pragma hdrstop

#include "Square.h"
#include <math.h>

Square :: Square(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

void Square :: Set(int a, int b, int c, int d)
	{
        x1 = a;
		y1 = b;
		if (c-a<d-b)
		{
			x2 = c;
			y2 = b + (c-a);
		}
		else
		{
			x2 = a + (d-b);
			y2 = d;
		}
		x3 = x1; y3 = y2; x4 = x2; y4 = y1;
	}

void Square :: show(TCanvas *Canvas)
	{
		Canvas->Pen->Color=clGreen;
		Canvas->Pen->Width=3;
		Canvas->MoveTo(x1, y1);
		Canvas->LineTo(x3, y3);
		Canvas->LineTo(x2, y2);
		Canvas->LineTo(x4, y4);
		Canvas->LineTo(x1, y1);
	}

float Square :: Area()
	{
		S = (float)((x2 - x1) * (x2 - x1));
		S = mod(S);
		return S;
	}

float Square :: Perimeter()
	{
		P = (float)((x2 - x1) * 4);
		P = mod(P);
		return P;
	}
////
int Square :: XCentMass()
	{
		X = x1 + (x2 - x1) / 2;
		return X;
	}
////
int Square :: YCentMass()
	{
		Y = y1 + (x2 - x1) / 2;
		return Y;
	}

void Square :: hide(TCanvas *Canvas)
	{
		Canvas->Pen->Color=clWhite;
		Canvas->Pen->Width=3;
		Canvas->MoveTo(x1, y1);
		Canvas->LineTo(x3, y3);
		Canvas->LineTo(x2, y2);
		Canvas->LineTo(x4, y4);
		Canvas->LineTo(x1, y1);
    }

void Square :: change(float side, int &x1, int &y1, int &x2, int &y2)
	{
		x1 =  X - side / 2;
		y1 =  Y - side / 2;
		x2 =  X + side / 2;
		y2 =  Y + side / 2;
	}
////
void Square :: Rotation(int &a1,int &b1,int &a2,int &b2,int &a3,int &b3,int &a4,int &b4)
	{
		int xh1, yh1, xh2, yh2, xh3, yh3, xh4, yh4;
		xh1 = (X + (x1 - X) * cos(0.2) - (y1 - Y) * sin(0.2));
		yh1 = (Y + (x1 - X) * sin(0.2) + (y1 - Y) * cos(0.2));
		xh2 = (X + (x2 - X) * cos(0.2) - (y2 - Y) * sin(0.2));
		yh2 = (Y + (x2 - X) * sin(0.2) + (y2 - Y) * cos(0.2));
		xh3 = (X + (x3 - X) * cos(0.2) - (y3 - Y) * sin(0.2));
		yh3 = (Y + (x3 - X) * sin(0.2) + (y3 - Y) * cos(0.2));
		xh4 = (X + (x4 - X) * cos(0.2) - (y4 - Y) * sin(0.2));
		yh4 = (Y + (x4 - X) * sin(0.2) + (y4 - Y) * cos(0.2));
		a1 = xh1;	b1 = yh1;
		a2 = xh2;	b2 = yh2;
		a3 = xh3;	b3 = yh3;
		a4 = xh4;	b4 = yh4;
	}

////
void Square :: SetForRotation(int a, int b, int c, int d, int e, int f, int g, int h)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
		x3 = e;
		y3 = f;
		x4 = g;
		y4 = h;
	}

#pragma package(smart_init)
