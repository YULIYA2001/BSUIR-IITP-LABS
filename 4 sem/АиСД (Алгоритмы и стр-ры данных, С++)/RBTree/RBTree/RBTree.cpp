#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

enum Color { RED, BLACK };

template <class T>
class RBTree
{
	public:
	struct Node
	{
		T key;
		Node* parent, * right, * left;
		Color color;

		Node(T key, Color color, Node* right, Node* left)
		{
			this->key = key;
			this->color = color;
			this->right = right;
			this->left = left;
		}
	};

	private:
	/*RBTree();
	~RBTree()
	{
		Clear(root);
	}

	void Clear(node_st* node)
	{
		if (!node) return;
		Clear(node->p1);
		Clear(node->p2);
		delete node;
	}*/

	Node* root = NULL;

	Node* grandparent(Node* n)
	{
		if ((n != NULL) && (n->parent != NULL))
			return n->parent->parent;
		else
			return NULL;
	}

	Node* uncle(Node* n)
	{
		Node* g = grandparent(n);
		if (g == NULL)
			// нет дедушки - нет дяди
			return NULL;
		if (n->parent == g->left)
			return g->right;
		else
			return g->left;
	}

	void leftRotate(Node* n)
	{
		Node* pivot = n->right;

		// при этом, возможно, pivot становится корнем дерева
		pivot->parent = n->parent;
		if (pivot->parent == NULL)
			root = pivot;
		if (n->parent != NULL)
		{
			if (n->parent->left == n)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
		}

		n->right = pivot->left;
		if (pivot->left != NULL)
			pivot->left->parent = n;

		n->parent = pivot;
		pivot->left = n;
	}

	void rightRotate(Node* n)
	{
		Node* pivot = n->left;

		// при этом, возможно, pivot становится корнем дерева 
		pivot->parent = n->parent;
		if (pivot->parent == NULL)
			root = pivot;
		if (n->parent != NULL)
		{
			if (n->parent->left == n)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
		}

		n->left = pivot->right;
		if (pivot->right != NULL)
			pivot->right->parent = n;

		n->parent = pivot;
		pivot->right = n;
	}

	void insert_case5(Node* n)
	{
		Node* g = grandparent(n);

		n->parent->color = BLACK;
		g->color = RED;
		if ((n == n->parent->left) && (n->parent == g->left))
		{
			rightRotate(g);
		}
		else
		{
			//(n == n->parent->right) && (n->parent == g->right)
			leftRotate(g);
		}
	}

	void insert_case4(Node* n)
	{
		Node* g = grandparent(n);

		if ((n == n->parent->right) && (n->parent == g->left))
		{
			leftRotate(n->parent);
			n = n->left;
		}
		else if ((n == n->parent->left) && (n->parent == g->right))
		{
			rightRotate(n->parent);
			n = n->right;
		}
		insert_case5(n);
	}

	void insert_case3(Node* n)
	{
		Node* u = uncle(n), * g;

		if ((u != NULL) && (u->color == RED))
		{
			// && (n->parent->color == RED) Второе условие проверяется в insert_case2, то есть родитель уже является красным.
			n->parent->color = BLACK;
			u->color = BLACK;
			g = grandparent(n);
			g->color = RED;
			insert_case1(g);
		}
		else
		{
			insert_case4(n);
		}
	}

	void insert_case2(Node* n)
	{
		if (n->parent->color == BLACK)
			return; // Tree is still valid
		else
			insert_case3(n);
	}

	void insert_case1(Node* n)
	{
		if (n->parent == NULL)
			n->color = BLACK;
		else
			insert_case2(n);
	}

	public:
	void insert(T key)
	{
		Node* t = new Node(key, RED, NULL, NULL);
		if (root == NULL)
		{
			root = t;
			t->parent = NULL;
		}
		else
		{
			Node* p = root;
			Node* q = NULL;
			while (p != NULL) // спускаемся вниз, пока не дойдем до подходящего листа 
			{
				q = p;
				if (p->key < t->key)
					p = p->right;
				else
					p = p->left;
			}
			t->parent = q;
			// добавляем новый элемент красного цвета 
			if (q->key < t->key)
				q->right = t;
			else
				q->left = t;
		}

		insert_case1(t);
	}

	private:
	Node* sibling(Node* n)
	{
		if (n == n->parent->left)
			return n->parent->right;
		else
			return n->parent->left;
	}

	void replace_node(Node* n, Node* child)
	{
		child->parent = n->parent;
		if (n == n->parent->left)
		{
			n->parent->left = child;
		}
		else
		{
			n->parent->right = child;
		}
	}

	void delete_case6(Node* n)
	{
		Node* s = sibling(n);

		s->color = n->parent->color;
		n->parent->color = BLACK;

		if (n == n->parent->left)
		{
			s->right->color = BLACK;
			leftRotate(n->parent);
		}
		else
		{
			s->left->color = BLACK;
			rightRotate(n->parent);
		}
	}

	void delete_case5(Node* n)
	{
		Node* s = sibling(n);

		if (s->color == BLACK)
		{
			if ((n == n->parent->left) && (s->right == NULL || s->right->color == BLACK) && (s->left->color == RED))
			{
				s->color = RED;
				s->left->color = BLACK;
				rightRotate(s);
			}
			else if ((n == n->parent->right) && (s->left->color == BLACK) && (s->right->color == RED))
			{
				s->color = RED;
				s->right->color = BLACK;
				leftRotate(s);
			}
		}
		delete_case6(n);
	}

	void delete_case4(Node* n)
	{
		Node* s = sibling(n);

		if ((n->parent->color == RED) && (s->color == BLACK) &&
			(s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK))
		{
			s->color = RED;
			n->parent->color = BLACK;
		}
		else
			delete_case5(n);
	}

	void delete_case3(Node* n)
	{
		Node* s = sibling(n);

		if ((n->parent->color == BLACK) && (s->color == BLACK) &&
			(s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK))
		{
			s->color = RED;
			delete_case1(n->parent);
		}
		else
			delete_case4(n);
	}

	void delete_case2(Node* n)
	{
		Node* s = sibling(n);

		if (s->color == RED)
		{
			n->parent->color = RED;
			s->color = BLACK;
			if (n == n->parent->left)
				leftRotate(n->parent);
			else
				rightRotate(n->parent);
		}
		delete_case3(n);
	}

	void delete_case1(Node* n)
	{
		if (n->parent != NULL)
			delete_case2(n);
	}

	public:
	void del(T key)
	{
		Node* p = root;

		// находим узел с ключом key
		while (p->key != key)
		{
			if (p->key < key)
				p = p->right;
			else
				p = p->left;
			if (p == NULL)
			{
				cout << "\nThere is no element with key " << key << "\n";
				return;
			}
		}

		// y - вершина, со следующим значением ключа (у нее нет левого ребенка) 
		Node* y = NULL;
		y = p->left;
		if (y == NULL)
			y = p;
		else
		{
			while (y->right != NULL)
				y = y->right;
		}
		p->key = y->key;

		if (y->color == RED)
		{
			if (y == y->parent->right)
				y->parent->right = NULL;
			else
				y->parent->left = NULL;
			delete y;
		}
		else
		{
			if (y->left != NULL || y->right != NULL)
			{
				if (y->left != NULL && y->left->color == RED)
				{
					if (y->parent != NULL)
					{
						if (y == y->parent->right)
							y->parent->right = y->left;
						else
							y->parent->left = y->left;
					}
					else
						root = y->left;
					y->left->parent = y->parent;
					y->left->color = BLACK;
					delete y;
				}
				else if (y->right != NULL && y->right->color == RED)
				{
					if (y->parent != NULL)
					{
						if (y == y->parent->right)
							y->parent->right = y->right;
						else
							y->parent->left = y->right;
					}
					else
						root = y->right;
					y->right->parent = y->parent;
					y->right->color = BLACK;
					delete y;
				}
			}
			else
			{
				if (y->parent == NULL)
					root = NULL;
				else
				{
					delete_case1(y);
					// replase node
					if (y == y->parent->right)
						y->parent->right = NULL;
					else
						y->parent->left = NULL;
				}
				delete y;
			}
		}
	}

	Node* find(T key)
	{
		Node* node = root;
		while (node)
		{
			if (node->key == key)
				return node;
			node = node->key > key ? node->left : node->right;
		}
		return NULL;
	}

	private:
	// вывод дерева: node узел, depth глубина, dir значок
	void Show(Node* node, int depth, char dir)
	{
		int n;
		if (!node)
			return;
		for (n = 0; n < depth; n++)
			cout << ' ';
		cout << dir << "[" << node->key << "](" << (node->color == RED ? "r" : "b") << ")\n";
		Show(node->left, depth + 2, '-');
		Show(node->right, depth + 2, '+');
	}

	public:
	// вывод дерева
	void Show()
	{
		cout << "-------------------\n";
		cout << "* for root\n- for left child\n+ for right child\n[key], (color)\n";
		cout << "-------------------\n";
		cout << "\nRed-Black Tree: \n\n";
		Show(root, 0, '*');
	}

	private:
	Node* minimum(Node* n)
	{
		while (n->left != NULL)
		{
			n = n->left;
		}
		return n;
	}

	Node* maximum(Node* n)
	{
		while (n->right != NULL)
		{
			n = n->right;
		}
		return n;
	}

	public:
	Node* nextNode(Node* x)
	{
		if (x->right != NULL)
			return minimum(x->right);
		Node* y = x->parent;
		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	Node* prevNode(Node* x)
	{
		if (x->left != NULL)
			return maximum(x->left);
		Node* y = x->parent;
		while (y != NULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}	
};

int main()
{
	// русский язык в консоли
	setlocale(LC_ALL, "Russian");

	// создать вектор на 1 млн элементов и перемешать элементы
	vector <int> v;
	for (int i = 0; i < 1000000; i++)
		v.push_back(i);
	random_shuffle(v.begin(), v.end());
	
	RBTree<int> tree;

	// измеряем время выполнения 1000000 вставок
	unsigned int start_time = clock();					// начальное время
	// добавить элементы перемешанного вектора в дерево
	for (int i = 0; i < 1000000; i++)
	{
		tree.insert(v[i]);
	}
	unsigned int end_time = clock();					// конечное время
	unsigned int search_time = end_time - start_time;	// искомое время
	cout << "\nВремя необходимое для выполнения 1 млн вставок: " << search_time<< "млс = "<<
		search_time/1000.0 << "с\n\n";

	// использование поиска и итерирования
	cout << "Итерирование с 999990 до конца:\n";
	RBTree<int>::Node* n = tree.find(999990);
	while (1)
	{
		cout << n->key << " ";
		n = tree.nextNode(n);
		if (n == NULL)
			break;
	}
	delete n;
	cout << "\n\nИтерирование с 10 до начала:\n";;
	RBTree<int>::Node* m = tree.find(10);
	while (1)
	{
		cout << m->key << " ";
		m = tree.prevNode(m);
		if (m == NULL)
			break;
	}
	delete m;
	cout << endl;
	
	//// вывод дерева на экран в виде дерева
	//cout << "Array:\n";
	//for (int i = 0; i < 10; i++)
	//	cout << v[i] << "   ";
	//cout << endl << endl;
	//tree.Show();

	//// удалить все элементы из дерева с выводом каждой итерации
	//for (int i = 0; i < 1000000; i++)
	//{
	//	tree.del(v[i]);
	//	cout << i <<"\n";
	//	tree.Show();
	//	cout << endl << endl;
	//}
	system("pause");
	return 0;
}