#include "Queue.h"

#ifndef Variant6H
#define Variant6H

class MyList : public Queue
{
	public:
    ~MyList();                           //деструктор (очищение списка)
	void RemoveMinus();                  //удаление отрицательных элементов
};

#endif
