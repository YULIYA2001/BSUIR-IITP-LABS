#ifndef HashH
#define HashH

#define compEQ(a,b) (a == b)
typedef int T;   //тип элементов

struct Node
{
	T data;
	Node *next;
};

class Hash
{
	public:
	Hash(int);
	Node *InsertNode(T);    // вставка элемента
	void DeleteNode(T);     // удаление элемента
	Node *FindNode(T);      // поиск элемента по данным
	int Index(T data);      // индекс в хеш-таблице
	Node **hashTable;       // указатель на массив указателей
	int hashTableSize;      // размер хеш-таблицы
};

#endif


