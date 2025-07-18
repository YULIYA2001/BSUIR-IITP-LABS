//---------------------------------------------------------------------------

#ifndef DiskH
#define DiskH

class Disk
{
    public:
    String type;
	String name;
	String author;
	String cost;
	String notes;
	String separator;
	Disk(){}
	Disk(String, String, String, String, String);
	~Disk(){};
	void ReadFromFile(TStringList *, int);    //������������� ������ ������
	void Add(int &, Disk *&, TMemo *);    //����������
	void Remove(int, int &, Disk *&);    //��������
	void Sort(int, int, Disk *);    //����������
	void Show(TMemo *);    //�������� ������� �����
};

#endif
