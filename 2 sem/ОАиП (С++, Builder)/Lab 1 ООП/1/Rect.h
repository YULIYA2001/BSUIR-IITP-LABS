//---------------------------------------------------------------------------

#ifndef RectH
#define RectH

class  Rect
{
    public:
	int x1,y1;
	Rect(){}  //����������� �� ���������
	Rect(int, int); //�����������
    ~Rect(){}   //����������
	virtual void show(TCanvas *Canvas);
	void moveRight(TCanvas *Canvas);
	void moveLeft(TCanvas *Canvas);
	void moveUp(TCanvas *Canvas);
	void moveDown(TCanvas *Canvas);
	virtual void hide(TCanvas *Canvas);
};

#endif
