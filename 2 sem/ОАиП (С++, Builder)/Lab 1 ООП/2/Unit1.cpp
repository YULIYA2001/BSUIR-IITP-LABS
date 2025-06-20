//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Figure.h"
#include "Circle.h"
#include "Rect.h"
#include "Square.h"
#include "Triangle.h"
#define PI 3.14159265358979323846
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int a1, b1, a2, b2; //координаты, считываемые при нажатии на холст
Circle C;
Rectan R;
Square S;
Triangle T;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//отображение при создании формы
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Image1->Canvas->Brush->Color=clWhite; //Устанавливаем цвет кисти
	Image1->Canvas->FloodFill(1,1,clWhite,fsSurface);
}

//очистка канвы при смене фигуры(можно убрать чтобы рисовать несколько)
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
    Image1->Canvas->Brush->Color=clWhite;
	Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
	Panel1->Caption="";
	Panel2->Caption="";
	Edit1->Text="0";
	Edit2->Text="0";
	Edit3->Text="0";
	Edit4->Text="";
	Edit5->Text="";
	Edit6->Text="";
	Edit7->Text="";
}

//координаты первой точки по зажатию мыши
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image1->Canvas->Brush->Color=clWhite;                             //очистка при рисовании новой фигуры того же вида
	Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height)); //(можно убрать чтобы рисовать несколько)
	a1 = X;
	b1 = Y;
}

//координаты второй точки по отпусканию мыши
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	a2 = X;
	b2 = Y;
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(C.Area());
			Panel2->Caption=FloatToStr(C.Perimeter());
			Edit1->Text=IntToStr(C.XCentMass());
			Edit2->Text=IntToStr(C.YCentMass());
			Edit3->Text=FloatToStr(C.Perimeter() / 2.0 / PI);
			break;
		}
		case 1:
		{
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(R.Area());
			Panel2->Caption=FloatToStr(R.Perimeter());
			Edit1->Text=IntToStr(R.XCentMass());
			Edit2->Text=IntToStr(R.YCentMass());
			Edit4->Text=IntToStr(a1);
			Edit5->Text=IntToStr(b1);
			Edit6->Text=IntToStr(a2);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(S.Area());
			Panel2->Caption=FloatToStr(S.Perimeter());
			Edit1->Text=IntToStr(S.XCentMass());
			Edit2->Text=IntToStr(S.YCentMass());
			Edit3->Text=FloatToStr((float)(S.Perimeter() / 4.0));
			break;
		}
		case 3:
		{
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(T.Area());
			Panel2->Caption=FloatToStr(T.Perimeter());
			Edit1->Text=IntToStr(T.XCentMass());
			Edit2->Text=IntToStr(T.YCentMass());
			Edit3->Text=FloatToStr((float)(T.Perimeter() / 3.0));
			break;
		}
	}
}
//обработчик кнопки для очистки холста
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Image1->Canvas->Brush->Color=clWhite;
	Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
	Panel1->Caption="";
	Panel2->Caption="";
	Edit1->Text="0";
	Edit2->Text="0";
	Edit3->Text="0";
	Edit4->Text="";
	Edit5->Text="";
	Edit6->Text="";
	Edit7->Text="";
}
//кнопка для подтверждения изменения центра масс
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	float newX, newY;
	bool check = 0;
	newX = StrToInt(Edit1->Text);
	newY = StrToInt(Edit2->Text);
	if (newX < 0 || newX > 850)
	{
		Edit1->Text="Wrong";
		check = true;
	}
	if (newY < 0 || newY > 570)
	{
		Edit2->Text="Wrong";
		check = true;
	}
	if (check == 0)
	{
		switch(RadioGroup1->ItemIndex)
		{
			case 0:
			{
				C.hide(Image1->Canvas);
				a1 += (newX - C.XCentMass());
				b1 += (newY - C.YCentMass());
				a2 += (newX - C.XCentMass());
				b2 += (newY - C.YCentMass());
				C.Set(a1, b1, a2, b2);
				C.XCentMass();
                C.YCentMass();
				C.show(Image1->Canvas);
				break;
			}
			case 1:
			{
				R.hide(Image1->Canvas);
				a1 += (newX - R.XCentMass());
				b1 += (newY - R.YCentMass());
				a2 += (newX - R.XCentMass());
				b2 += (newY - R.YCentMass());
				R.Set(a1, b1, a2, b2);
				R.XCentMass();
				R.YCentMass();
				R.show(Image1->Canvas);
				Edit4->Text=IntToStr(a1);
				Edit5->Text=IntToStr(b1);
				Edit6->Text=IntToStr(a2);
				Edit7->Text=IntToStr(b2);
				break;
			}
			case 2:
			{
				S.hide(Image1->Canvas);
				a1 += (newX - S.XCentMass());
				b1 += (newY - S.YCentMass());
				a2 += (newX - S.XCentMass());
				b2 += (newY - S.YCentMass());
				S.Set(a1, b1, a2, b2);
				S.XCentMass();
				S.YCentMass();
				S.show(Image1->Canvas);
				break;
			}
			case 3:
			{
				T.hide(Image1->Canvas);
				a1 += (newX - T.XCentMass());
				b1 += (newY - T.YCentMass());
				a2 += (newX - T.XCentMass());
				b2 += (newY - T.YCentMass());
				T.Set(a1, b1, a2, b2);
				T.XCentMass();
				T.YCentMass();
				T.show(Image1->Canvas);
				break;
			}
		}
	}
}
//кнопка для движения вверх
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Timer4->Enabled = true;
}
//таймер для движения вверх
void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.hide(Image1->Canvas);
			C.moveUp(a1, b1, a2, b2);
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Edit2->Text=IntToStr(C.YCentMass());
			break;
		}
		case 1:
		{
			R.hide(Image1->Canvas);
			R.moveUp(a1, b1, a2, b2);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Edit2->Text=IntToStr(R.YCentMass());
			Edit5->Text=IntToStr(b1);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.moveUp(a1, b1, a2, b2);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Edit2->Text=IntToStr(S.YCentMass());
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.moveUp(a1, b1, a2, b2);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Edit2->Text=IntToStr(T.YCentMass());
			break;
		}
	}
}

//кнопка для движения вниз
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Timer3->Enabled = true;
}
//таймер для движения вниз
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.hide(Image1->Canvas);
			C.moveDown(a1, b1, a2, b2);
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Edit2->Text=IntToStr(C.YCentMass());
			break;
		}
		case 1:
		{
			R.hide(Image1->Canvas);
			R.moveDown(a1, b1, a2, b2);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Edit2->Text=IntToStr(R.YCentMass());
			Edit5->Text=IntToStr(b1);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.moveDown(a1, b1, a2, b2);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Edit2->Text=IntToStr(S.YCentMass());
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.moveDown(a1, b1, a2, b2);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Edit2->Text=IntToStr(T.YCentMass());
			break;
		}
	}
}

//кнопка для движения вправо
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Timer2->Enabled = true;
}

//таймер для движения вправо
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.hide(Image1->Canvas);
			C.moveRight(a1, b1, a2, b2);
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Edit1->Text=IntToStr(C.XCentMass());
			break;
		}
		case 1:
		{
			R.hide(Image1->Canvas);
			R.moveRight(a1, b1, a2, b2);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Edit1->Text=IntToStr(R.XCentMass());
			Edit4->Text=IntToStr(a1);
			Edit6->Text=IntToStr(a2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.moveRight(a1, b1, a2, b2);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Edit1->Text=IntToStr(S.XCentMass());
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.moveRight(a1, b1, a2, b2);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Edit1->Text=IntToStr(T.XCentMass());
			break;
		}
	}
}

//кнопка для движения влево
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Timer1->Enabled = true;
}

//таймер для движения влево
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.hide(Image1->Canvas);
			C.moveLeft(a1, b1, a2, b2);
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Edit1->Text=IntToStr(C.XCentMass());
			break;
		}
		case 1:
		{
			R.hide(Image1->Canvas);
			R.moveLeft(a1, b1, a2, b2);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Edit1->Text=IntToStr(R.XCentMass());
            Edit4->Text=IntToStr(a1);
			Edit6->Text=IntToStr(a2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.moveLeft(a1, b1, a2, b2);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Edit1->Text=IntToStr(S.XCentMass());
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.moveLeft(a1, b1, a2, b2);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Edit1->Text=IntToStr(T.XCentMass());
			break;
		}
	}
}

//отключение таймеров для движения
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Timer1->Enabled = false;
	Timer2->Enabled = false;
	Timer3->Enabled = false;
	Timer4->Enabled = false;
}

//кнопка увеличения фигуры
void __fastcall TForm1::Button8Click(TObject *Sender)
{
    Timer5->Enabled = true;
}

//таймер увеличения фигуры
void __fastcall TForm1::Timer5Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.hide(Image1->Canvas);
			C.Bigger(a1, b1, a2, b2);
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(C.Area());
			Panel2->Caption=FloatToStr(C.Perimeter());
			Edit3->Text=FloatToStr(C.Perimeter() / 2.0 / PI);
			break;
		}
		case 1:
		{
			R.hide(Image1->Canvas);
			R.Bigger(a1, b1, a2, b2);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(R.Area());
			Panel2->Caption=FloatToStr(R.Perimeter());
			Edit4->Text=IntToStr(a1);
			Edit5->Text=IntToStr(b1);
			Edit6->Text=IntToStr(a2);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.Bigger(a1, b1, a2, b2);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(S.Area());
			Panel2->Caption=FloatToStr(S.Perimeter());
			Edit3->Text=FloatToStr((float)(S.Perimeter() / 4.0));
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.Bigger(a1, b1, a2, b2);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(T.Area());
			Panel2->Caption=FloatToStr(T.Perimeter());
			Edit3->Text=FloatToStr((float)(T.Perimeter() / 3.0));
			break;
		}
	}
}

//кнопка уменьшения фигуры
void __fastcall TForm1::Button9Click(TObject *Sender)
{
	Timer6->Enabled = true;
}

//таймер уменьшения фигуры
void __fastcall TForm1::Timer6Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 0:
		{
			C.hide(Image1->Canvas);
			C.Smaller(a1, b1, a2, b2);
			C.Set(a1, b1, a2, b2);
			C.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(C.Area());
			Panel2->Caption=FloatToStr(C.Perimeter());
			Edit3->Text=FloatToStr(C.Perimeter() / 2.0 / PI);
			break;
		}
		case 1:
		{
			R.hide(Image1->Canvas);
			R.Smaller(a1, b1, a2, b2);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(R.Area());
			Panel2->Caption=FloatToStr(R.Perimeter());
            Edit4->Text=IntToStr(a1);
			Edit5->Text=IntToStr(b1);
			Edit6->Text=IntToStr(a2);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.Smaller(a1, b1, a2, b2);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(S.Area());
			Panel2->Caption=FloatToStr(S.Perimeter());
			Edit3->Text=FloatToStr((float)(S.Perimeter() / 4.0));
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.Smaller(a1, b1, a2, b2);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(T.Area());
			Panel2->Caption=FloatToStr(T.Perimeter());
			Edit3->Text=FloatToStr((float)(T.Perimeter() / 3.0));
			break;
		}
	}
}

//отключение масштабирования
void __fastcall TForm1::Button10Click(TObject *Sender)
{
	Timer5->Enabled = false;
	Timer6->Enabled = false;
}

//кнопка начала вращения
int a1copy, b1copy, a2copy, b2copy;
void __fastcall TForm1::Button11Click(TObject *Sender)
{
    if(RadioGroup1->ItemIndex==0)
		Timer6->Enabled = false;
	else Timer7->Enabled = true;
	//для запоминания положения фигур до вращения
	a1copy=a1; b1copy=b1; a2copy=a2; b2copy=b2;
}
//таймер вращения
void __fastcall TForm1::Timer7Timer(TObject *Sender)
{
	switch(RadioGroup1->ItemIndex)
	{
		case 1:
		{
			int a3, b3, a4, b4;
			R.hide(Image1->Canvas);
			R.Rotation(a1, b1, a2, b2, a3, b3, a4, b4);
			R.SetForRotation(a1, b1, a2, b2, a3, b3, a4, b4);
			R.show(Image1->Canvas);
			Edit4->Text=IntToStr(a1);
			Edit5->Text=IntToStr(b1);
			Edit6->Text=IntToStr(a2);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			int a3, b3, a4, b4;
			S.hide(Image1->Canvas);
			S.Rotation(a1, b1, a2, b2, a3, b3, a4, b4);
			S.SetForRotation(a1, b1, a2, b2, a3, b3, a4, b4);
			S.show(Image1->Canvas);
			break;
		}
		case 3:
		{
			int a3, b3;
			T.hide(Image1->Canvas);
			T.Rotation(a1, b1, a2, b2, a3, b3);
			T.SetForRotation(a1, b1, a2, b2, a3, b3);
			T.show(Image1->Canvas);
			break;
		}
	}
}
//кнопка завершения вращения
void __fastcall TForm1::Button12Click(TObject *Sender)
{
	Timer7->Enabled = false;
	//возвращение фигур в положение до вращения
	a1=a1copy; b1=b1copy; a2=a2copy; b2=b2copy;
    switch(RadioGroup1->ItemIndex)
	{
		case 1:
		{
			R.hide(Image1->Canvas);
			R.Set(a1, b1, a2, b2);
			R.show(Image1->Canvas);
			Edit4->Text=IntToStr(a1);
			Edit5->Text=IntToStr(b1);
			Edit6->Text=IntToStr(a2);
			Edit7->Text=IntToStr(b2);
			break;
		}
		case 2:
		{
			S.hide(Image1->Canvas);
			S.Set(a1, b1, a2, b2);
			S.show(Image1->Canvas);
			break;
		}
		case 3:
		{
			T.hide(Image1->Canvas);
			T.Set(a1, b1, a2, b2);
			T.show(Image1->Canvas);
			break;
		}
	}
}

//изменение характерных параметров фигуры
void __fastcall TForm1::Button13Click(TObject *Sender)
{
	if(RadioGroup1->ItemIndex==1)
	{
		if(Edit3->Text == "0" && Edit4->Text == "")
			Edit3->Text = "Wrong";
		else
		{
			int a, b, c, d;
			a = StrToInt(Edit4->Text);
			if (a < 0)
				Edit4->Text="Wrong";
			b = StrToInt(Edit5->Text);
			if (a < 0)
				Edit5->Text="Wrong";
			c = StrToInt(Edit6->Text);
			if (a < 0)
				Edit6->Text="Wrong";
			d = StrToInt(Edit7->Text);
			if (a < 0)
				Edit7->Text="Wrong";
			R.hide(Image1->Canvas);
			a1=a; b1=b; a2=c; b2=d;
			R.Set(a1, b1, a2, b2);  //изменение координат прямоугольника
			R.show(Image1->Canvas);
			Panel1->Caption=FloatToStr(R.Area());
			Panel2->Caption=FloatToStr(R.Perimeter());
			Edit1->Text=IntToStr(R.XCentMass());
			Edit2->Text=IntToStr(R.YCentMass());
		}
	}
	else
	{
		float size;
		size = StrToFloat(Edit3->Text);
		if (size <= 0)
			Edit3->Text="Wrong";
		else
		{
			switch(RadioGroup1->ItemIndex)
			{
				case 0:
				{
					C.hide(Image1->Canvas);
					C.change(size, a1, b1, a2, b2);
					C.Set(a1, b1, a2, b2);
					C.show(Image1->Canvas);
					Panel1->Caption=FloatToStr(C.Area());
					Panel2->Caption=FloatToStr(C.Perimeter());
					break;
				}
				case 2:
				{
					S.hide(Image1->Canvas);
					S.change(size, a1, b1, a2, b2);
					S.Set(a1, b1, a2, b2);
					S.show(Image1->Canvas);
					Panel1->Caption=FloatToStr(S.Area());
					Panel2->Caption=FloatToStr(S.Perimeter());
					break;
				}
				case 3:
				{
					T.hide(Image1->Canvas);
					T.change(size, a1, b1, a2, b2);
					T.Set(a1, b1, a2, b2);
					T.show(Image1->Canvas);
					Panel1->Caption=FloatToStr(T.Area());
					Panel2->Caption=FloatToStr(T.Perimeter());
					break;
				}
			}
		}
	}
}
