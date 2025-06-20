//---------------------------------------------------------------------------

#pragma hdrstop

#include "Disk.h"

Disk :: Disk(String type, String name, String author, String cost, String notes)
	{
		this->type = type;
		this->name = name;
		this->author = author;
		this->cost = cost;
		this->notes = notes;
	}

void Disk :: ReadFromFile(TStringList *List, int x)
	{
		this->type = List->Strings[x];
		this->name = List->Strings[++x];
		this->author = List->Strings[++x];
		this->cost = List->Strings[++x];
		this->notes = List->Strings[++x];
		this->separator = List->Strings[++x];
	}

void Disk :: Show(TMemo *Memo1)
	{
		Memo1->Lines->Add(type);
		Memo1->Lines->Add(name);
		Memo1->Lines->Add(author);
		Memo1->Lines->Add(cost);
		Memo1->Lines->Add(notes);
		Memo1->Lines->Add(separator);
	}

void Disk :: Add(int &length, Disk *&disk, TMemo *Memo2)
	{
		Disk *temp = new Disk[length + 1];  //массив объектов на 1 больше
		for (int i = 0; i < length; i++)
		{
			temp[i] = disk[i];  //копирование из старого
		}
		delete []disk;
		//заполнение последнего объекта увеличенного массива
		temp[length].type = Memo2->Lines->Strings[0];
		temp[length].name = Memo2->Lines->Strings[1];
		temp[length].author = Memo2->Lines->Strings[2];
		temp[length].cost = Memo2->Lines->Strings[3];
		temp[length].notes = Memo2->Lines->Strings[4];
		temp[length].separator = "\n";
		disk = temp;
		length++;
	}

void Disk :: Remove(int ItemIndex, int &length, Disk *&disk)
	{
		Disk *temp = new Disk[length - 1];      //массив объектов на 1 меньше
		for (int i = ItemIndex; i < length - 1; i++)
		{
			disk[i] = disk[i + 1];   //сдвиг объектов (удаление нужного объекта)
		}
		for (int i = 0; i < length - 1; i++)
		{
			temp[i] = disk[i];    //копирование из старого (кроме последнего)
		}
		delete []disk;
		disk = temp;
		length--;
    }

void Disk :: Sort(int ItemIndex, int length, Disk *disk)
	{   //сортировка пузырьком
		Disk temp;
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = i + 1; j < length; j++)
			{
				//сортировка по наименованию
				if(ItemIndex == 1)
				{
					if (disk[i].name > disk[j].name)
					{
						temp = disk[i];
						disk[i] = disk[j];
						disk[j] = temp;
					}
				}
				//сортировка по автору
				else if(ItemIndex == 0)
                {
					if (disk[i].author > disk[j].author)
					{
						temp = disk[i];
						disk[i] = disk[j];
						disk[j] = temp;
					}
				}
			}
		}
	}

#pragma package(smart_init)
