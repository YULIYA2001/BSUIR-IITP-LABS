#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Disk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//���������� �������� ��������� �� ������ �������� ������ � ��� �����
Disk *disk;
int length;
TStringList *List;
//��� �������� �����
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//�������� ����������� ����� � ������ �����
	List = new TStringList;
	try
	{
		List->LoadFromFile("Disk.txt");
	}
	catch(...)
	{
		ShowMessage("���� \"Disk.txt\" �� ������");
	}
	//�������� ������������ ���������� �������� ������ � ������������ �������
	length = List->Count / 6;
	disk = new Disk[length];
	//������������� ����� ������
	for(int i = 0, x = 0; i < length; i++, x+=6)
	{
		disk[i].ReadFromFile(List, x);		ComboBox1->Items->Add(disk[i].type);	}	ComboBox1->ItemIndex = 0;	ComboBox1Change(NULL);}
//��������� Edit ��� ������ ������� �������� � ComboBox
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	Memo1->Lines->Clear();
	int i = ComboBox1->ItemIndex;
	Edit1->Text=disk[i].name;	Edit2->Text=disk[i].author;	Edit3->Text=disk[i].cost;	Edit4->Text=disk[i].notes;
}
//������ "���������"
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	for(int i = 0; i < length; i++)
	{
		disk[i].Show(Memo1);
	}
	Memo1->Lines->SaveToFile("Disk.txt");
	Application->Title="Success";
	ShowMessage("���������� ��������� �������");
	Memo1->Lines->Clear();
}
//�������� ������ � ���� ��� ������� ������ "���������� �����"
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	List->LoadFromFile("Disk.txt");
	for(int i = 0; i < List->Count; i++)
	{
		Memo1->Lines->Add(List->Strings[i]);
	}
}
//������ "������� ����������"
void __fastcall TForm1::Button8Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	for(int i = 0; i < length; i++)
	{
		disk[i].Show(Memo1);
	}
}
//������ "��������"
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	int check = 0;
	//�������� �� ������ ���������� ������
	if (Memo2->Lines->Count != 5)
	{
		Application->Title="������!";
		ShowMessage("�������� ������ ��� ����������");
	}
	else
	{
		//�������� �� ������� ������
		for (int i = 0; i < 5; i++)
		{
			if (Memo2->Lines->Strings[i] != "")
				check ++;
		}
		if (check == 5) //���� ������ �������
		{
			disk->Add(length, disk, Memo2);
			ComboBox1->Items->Add(Memo2->Lines->Strings[0]);
            for(int i = 0; i < length; i++)
			{
				disk[i].Show(Memo1);
			}
		}
		else   //���� ������ ����
		{
			Application->Title="������!";
			ShowMessage("�������� ������ ��� ����������");
		}
	}
	Memo2->Lines->Clear();
}
//������ "�������"
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	if(ComboBox1->Items->Strings[0] == "")  //���� ��� ������ �������
	{
		Application->Title="������!";
		ShowMessage("������ �� �������");
	}
	else
	{
		disk->Remove(ComboBox1->ItemIndex, length, disk);
		ComboBox1->Items->Delete(ComboBox1->ItemIndex);
		if (ComboBox1->Items->Strings[0] == "")  //���� ������ �� �������� -> ������� ���� �����
		{
			ComboBox1->Clear();
			Edit1->Text="";
			Edit2->Text="";			Edit3->Text="";			Edit4->Text="";		}
		else
		{   //���� ����� �������� -> ��������� ComboBox � Edit-�
			ComboBox1->ItemIndex = 0;
			ComboBox1Change(NULL);
			for(int i = 0; i < length; i++)
			{
				disk[i].Show(Memo1);
			}
		}
	}
}
//������ "�����������"
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	disk->Sort(RadioGroup1->ItemIndex,length, disk);
	//����� ������������ � ComboBox
	ComboBox1->Items->Clear();
	for(int i = 0; i < length; i++)
	{
		ComboBox1->Items->Add(disk[i].type);	}
	ComboBox1->ItemIndex = 0;
	ComboBox1Change(NULL);
    //�������� ���������������
	for(int i = 0; i < length; i++)
	{
		disk[i].Show(Memo1);
	}
}
//������ "�����"
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	bool check = false;
	Memo1->Lines->Clear();
	for (int i = 0; i < length; i++)
	{
		if (disk[i].author == Edit5->Text || disk[i].name == Edit5->Text)
		{
			disk[i].Show(Memo1);
			ComboBox1->ItemIndex = i;
			Edit1->Text=disk[i].name;
			Edit2->Text=disk[i].author;			Edit3->Text=disk[i].cost;			Edit4->Text=disk[i].notes;
			check = true;
		}
	}
	if(!check)
	{
		Application->Title="������!";
		ShowMessage("������ �� �������");
	}
	Edit5->Clear();
}
//������ "�����"
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Form1->Close();
	delete []disk;
}
//������ �������� ������ �� ��������� memo
void __fastcall TForm1::Memo1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	HideCaret(Memo1->Handle);
}

