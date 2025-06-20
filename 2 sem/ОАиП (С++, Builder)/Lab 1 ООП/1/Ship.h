//---------------------------------------------------------------------------

#ifndef ShipH
#define ShipH

#include "Rect.h"

class  Ship: public Rect
{
	public:
	Ship(){}  //конструктор по умолчанию
	Ship(int, int);//конструктор
	~Ship(){}   //деструктор
	void show(TCanvas *Canvas);
    void hide(TCanvas *Canvas);
};

#endif
