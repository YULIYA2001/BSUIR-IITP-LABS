//---------------------------------------------------------------------------

#ifndef ShipH
#define ShipH

#include "Rect.h"

class  Ship: public Rect
{
	public:
	Ship(){}  //����������� �� ���������
	Ship(int, int);//�����������
	~Ship(){}   //����������
	void show(TCanvas *Canvas);
    void hide(TCanvas *Canvas);
};

#endif
