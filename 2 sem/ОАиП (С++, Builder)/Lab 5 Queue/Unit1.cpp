#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Queue.h"
#include "Variant6.h"
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Queue queue;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//кнопка "Создать" для очереди
void __fastcall TForm1::CreateButtonClick(TObject *Sender)
{
	//удаление прошлой очереди
	queue.~Queue();
	ShowListBox->Clear();
	//если не введен размер
	if (QueueSizeEdit->Text == "" || QueueSizeEdit->Text == "0")
	{
		Application->Title = "Подсказка";
		ShowMessage("1. Введите \"Размер очереди\""
			"\n2. Запишите элементы в поле \"Очередь\""
			"\n3. Нажмите кнопку \"Создать\"");
	}   
	//если размер не соответствует кол-ву введенных элементов
	else if (AddQueueMemo->Lines->Count != StrToInt(QueueSizeEdit->Text))
	{
		Application->Title = "Подсказка";
		ShowMessage("1. Запишите элементы в поле \"Очередь\""
			"\n2. Проверте количество введенных элементов"
			"\n3. Нажмите кнопку \"Создать\"");	
	}
	else
	{
		bool check = true;     //идентификатор ввода пустой строки
		int length = AddQueueMemo->Lines->Count;
		//проверка ввода пустой строки
		for (int i = 0; i < length; i++)
		{                                              
			if (AddQueueMemo->Lines->Strings[i] == "")
			{
				check = false;
			}
			int strLength = AddQueueMemo->Lines->Strings[i].Length();
			for (int j = 2; j <= strLength; j++)
			{
				if (AddQueueMemo->Lines->Strings[i][j] == '-')
					check = false;	
            }
		}
		if (!check)
		{
			Application->Title = "Ошибка";                
			ShowMessage("Ввод только целых");
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				int x = StrToInt(AddQueueMemo->Lines->Strings[i]);
				queue.Add(x);
			}
		}
		AddQueueMemo->Clear();
		ShowListBox->Clear();
		//PrintButtonClick(Sender);
	}
}

//кнопка "Печать"
void __fastcall TForm1::PrintButtonClick(TObject *Sender)
{
	ShowListBox->Clear();
	queue.Show(ShowListBox);
	if (ShowListBox->Items->Count == 0)
		ShowListBox->Items->Add("Очередь пуста");
}

//кнопка "Добавить в конец"
void __fastcall TForm1::AddToEndButtonClick(TObject *Sender)
{
	ShowListBox->Clear();
	if (AddElementEdit->Text != "")
	{
		ShowListBox->Clear();
		int x = StrToInt(AddElementEdit->Text);
		queue.Add(x);
		QueueSizeEdit->Text = IntToStr(StrToInt(QueueSizeEdit->Text) + 1);
		AddElementEdit->Text = "";
		PrintButtonClick(Sender);
	}
	else 
	{
		Application->Title = "Подсказка";
		ShowMessage("Введите элемент для добавления");
	}
}

//кнопка "Извлечь из начала"
void __fastcall TForm1::TakeFromBeginButtonClick(TObject *Sender)
{
	ShowListBox->Clear();
	queue.Delete(QueueSizeEdit);
	PrintButtonClick(Sender);
}

//кнопка "Проверить пустоту"
void __fastcall TForm1::IsEmptyButtonClick(TObject *Sender)
{
   ShowListBox->Clear();
   queue.IsEmpty(QueueSizeEdit);
}

//кнопка "Очистить"
void __fastcall TForm1::CleanButtonClick(TObject *Sender)
{
	queue.~Queue();
	ShowListBox->Clear();
	QueueSizeEdit->Text = "0";
	Application->Title = "Очистка";
	ShowMessage("Очередь пуста");	
}

//переход в Memo1 при нажатии Enter после ввода размера очереди
void __fastcall TForm1::QueueSizeEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	//если введен enter
	if(Key == VK_RETURN)
	{
		Key = 0;
		AddQueueMemo->SetFocus();
	}	
}

MyList myList;

//кнопка "Решение" для списка
void __fastcall TForm1::MySolutionButtonClick(TObject *Sender)
{
	//удаление прошлого списка
	myList.~MyList();
	ShowMyTaskListBox->Clear();
	//если не введен размер
	if (ListSizeEdit->Text == "" || ListSizeEdit->Text == "0")
	{
		Application->Title = "Подсказка";
		ShowMessage("Введите \"Размер списка\"");
	}
	else
	{
		Application->Title = "Условие";
		ShowMessage("\tСоздать двухсвязный список из случайных целых чисел."
			" Удалить все отрицательные элементы списка");
		//случайное заполнение
		int amount = StrToInt(ListSizeEdit->Text);
		randomize();
		for (int i = 0; i < amount; i++)
		{
			myList.Add(rand() % 101 - 50); //заполнение числами от -50 до 50
		}
		ShowMyTaskListBox->Items->Add("Исходный:");
		myList.Show(ShowMyTaskListBox);
		myList.RemoveMinus();
		ShowMyTaskListBox->Items->Add("Без отрицат.");
		ShowMyTaskListBox->Items->Add("элементов:");
		myList.Show(ShowMyTaskListBox);
	}
}

//проверка на ввод целых в Memo1
void __fastcall TForm1::AddQueueMemoKeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((Key >= '0' && Key <= '9') || Key == '-' || Key == VK_BACK 
		|| Key == VK_RETURN);
	else 
	{
		Key = '0';                                                 
		Application->Title = "Ошибка";                
		ShowMessage("Ввод только целых");
	}                                      	
}


