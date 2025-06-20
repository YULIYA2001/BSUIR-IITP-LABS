#ifndef MyTask6H
#define MyTask6H

#include "Tree.h"

class MyTask : public Tree
{
	public:
	//удаление из левой ветви узла с max значением и всех связанных с ним
	void DeleteMaxLeftWithConnected(TTree **root, TMemo*);
    private:
	TTree* SearchMaxKey(TTree*, TTree **prev);   //нахождение максимального ключа
};

#endif
