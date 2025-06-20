//---------------------------------------------------------------------------

#pragma hdrstop

#include "Triangle.h"
#include <Math.h>
#define RAD_60 1.047197551196597746154214461093

Triangle :: Triangle(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

void Triangle :: Set(int a, int b, int c, int d)
	{
		helpSide = sqrt((c - a) * (c - a) + (d - b) * (d - b));
		x1 = a;
		y1 = b;
		x2 = a + helpSide;
		y2 = b;
		x3 = a + helpSide / 2;
		y3 = b + helpSide*sin(RAD_60);
	}

void Triangle :: show(TCanvas *Canvas)
	{
		Canvas->Pen->Color=clBlue;
		Canvas->Pen->Width=3;
		Canvas->MoveTo(x1, y1);
		Canvas->LineTo(x2, y2);
		Canvas->LineTo(x3, y3);
		Canvas->LineTo(x1, y1);
	}

float Triangle :: Area()
	{
		helpSide = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		S = (float)(0.5 * helpSide * helpSide * sin(RAD_60));
		return S;
	}

float Triangle :: Perimeter()
	{
		helpSide = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		P = helpSide * 3;
		return P;
	}

int Triangle :: XCentMass()
	{
		X = (int)x3;
		return X;
	}

int Triangle :: YCentMass()
	{
		Y = (int)(y1 + (y3 - y1) / 3);
		return Y;
	}

void Triangle :: hide(TCanvas *Canvas)
	{
		Canvas->Pen->Color=clWhite;
		Canvas->Pen->Width=3;
		Canvas->MoveTo(x1, y1);
		Canvas->LineTo(x2, y2);
		Canvas->LineTo(x3, y3);
		Canvas->LineTo(x1, y1);
	}

void Triangle :: change(float side, int &x1, int &y1, int &x2, int &y2)
	{
		x1 =  X - side / 2;
		y1 =  Y - (side * sin(RAD_60) / 3);
		x2 =  X + side / 2;
		y2 =  Y - (side * sin(RAD_60) / 3);
	}

void Triangle :: Rotation(int &a1,int &b1,int &a2,int &b2,int &a3,int &b3)
	{
		int xh1, yh1, xh2, yh2, xh3, yh3;
		xh1 = (X + (x1 - X) * cos(0.2) - (y1 - Y) * sin(0.2));
		yh1 = (Y + (x1 - X) * sin(0.2) + (y1 - Y) * cos(0.2));
		xh2 = (X + (x2 - X) * cos(0.2) - (y2 - Y) * sin(0.2));
		yh2 = (Y + (x2 - X) * sin(0.2) + (y2 - Y) * cos(0.2));
		xh3 = (X + (x3 - X) * cos(0.2) - (y3 - Y) * sin(0.2));
		yh3 = (Y + (x3 - X) * sin(0.2) + (y3 - Y) * cos(0.2));
        a1 = xh1;	b1 = yh1;
		a2 = xh2;	b2 = yh2;
		a3 = xh3;	b3 = yh3;
	}

void Triangle :: SetForRotation(int a, int b, int c, int d, int e, int f)
	{
        x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
		x3 = e;
		y3 = f;
	}


#pragma package(smart_init)
