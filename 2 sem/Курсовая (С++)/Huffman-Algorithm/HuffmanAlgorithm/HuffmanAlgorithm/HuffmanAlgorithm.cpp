#include "HuffmanAlgorithm.h"

// Функция для выделения нового узла дерева
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// проходим дерево Хаффмана и сохраняем коды Хаффмана в map
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == NULL)
		return;

	// найден лист
	if (root->left == NULL && root->right == NULL)
		huffmanCode[root->ch] = str;

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// проходим дерево Хаффмана и декодируем закодированную строку
void decode(Node* root, int& index, string str)
{
	if (root == NULL)
		return;

	// найден лист
	if (root->left == NULL && root->right == NULL)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

// печать дерева Хаффмана
void printTree(Node* root, unsigned k)
{
	if (root != NULL)
	{
		printTree(root->left, k + 3);
		for (unsigned i = 0; i < k; i++)
			cout << " ";
		if (root->ch)
			cout << root->freq << " (" << root->ch << ")" << endl;
		else
			cout << root->freq << endl;
		printTree(root->right, k + 3);
	}
}

// Строим дерево Хаффмана и декодируем заданный входной текст
void buildHuffmanTree(string text, int lan)
{
	// подсчитываем частоту появления каждого символа и сохраняем его в map
	unordered_map<char, int> freq;
	for (char ch : text)
		freq[ch]++;

	// вывод частот символов на экран с помощью итератора
	if (lan == '1')
		cout << "\nSymbol : frequency\n-----------------------" << endl;
	else
		cout << "\nСимвол : частота\n-----------------------" << endl;
	unordered_map<char, int>::iterator i;
	for (i = freq.begin(); i != freq.end(); ++i)
		cout << "  " << i->first << " : " << i->second << endl;

	// Создать приоритетную очередь для хранения узлов дерева Хаффмана
	priority_queue<Node*, vector<Node*>, comparison> pq;

	// Создание листа для каждого символа и добавление его в очередь приоритетов
	for (i = freq.begin(); i != freq.end(); ++i)
		pq.push(getNode(i->first, i->second, NULL, NULL));

	// пока в очереди не останется 1 узел (корень дерева)
	while (pq.size() != 1)
	{
		// Удалить два узла с наивысшим приоритетом (самая низкая частота встречаемости) из очереди
		// записать их в два листа для дерева
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();

		// Создать узел с двумя листами в качестве дочерних и с частотой, равной сумме их частот
		int sumfreq = left->freq + right->freq;
		// Добавить новый узел в очередь приоритетов
		pq.push(getNode('\0', sumfreq, left, right));
	}

	// корень хранит указатель на корень дерева Хаффмана
	Node* root = pq.top();

	// печать дерева Хаффмана
	if (lan == '1')
		cout << "\nHUFFMAN TREE\n-------------------------" << endl;
	else
		cout << "\nДерево Хаффмана\n-------------------------" << endl;
	printTree(root);


	// Проход по Дереву Хаффмана и сохранение двоичных кодов Хаффмана в map
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	// печать символ - двоичный код
	if (lan == '1')
		cout << "\nSymbol : its code\n-----------------------\n";
	else
		cout << "\nСимвол : его код\n-----------------------\n";
	unordered_map<char, string>::iterator it;
	for (it = huffmanCode.begin(); it != huffmanCode.end(); ++it)
		cout << "  " << it->first << " : " << it->second << '\n';

	if (lan == '1')
		cout << "\nOriginal string:\n" << text << '\n';
	else
		cout << "\nИсходная строка:\n" << text << '\n';

	// исходная строка  в двоичном виде
	if (lan == '1')
		cout << "\nCode of original string: " << endl;
	else
		cout << "\nДвоичный код исходной строки: " << endl;
	int textlen = 0;
	for (unsigned i = 0; i < text.length(); i++)
	{
		int k = 128;	//k= 10000000b
		while (k > 0)
		{
			cout << bool(text[i] & k);		// печатаем нужный разряд
			textlen++;
			k = k >> 1;		//сдвигаем k поразрядно вправо на 1
		}
	}
	cout << endl;

	// печать закодированной строки
	string str = "";
	string::iterator ch;
	for (ch = text.begin(); ch != text.end(); ++ch)
		str += huffmanCode[*ch];
	if (lan == '1')
		cout << "\nEncoded string:\n" << str << '\n';
	else
		cout << "\nЗакодированная строка:\n" << str << '\n';
	// проход дерева Хаффмана и декодирование строки
	int index = -1;
	if (lan == '1')
		cout << "\nDecoded string: \n";
	else
		cout << "\nРаскодированная строка: \n";
	while (index < (int)str.size() - 2)
		decode(root, index, str);
	cout << endl;

	// коэфициент сжатия строки
	double compressionRatio = (double)textlen / (double)str.size();
	if (lan == '1')
		cout << "\nCompression ratio: k = " << fixed << setprecision(2) << compressionRatio << endl;
	else
		cout << "\nКоэффициент сжатия: k = " << fixed << setprecision(2) << compressionRatio << endl;
	// сжатие в %
	compressionRatio = 100.0 - 100.0 / compressionRatio;
	if (lan == '1')
		cout << "Compression in %: " << fixed << setprecision(2) << compressionRatio << " %\n" << endl;
	else
		cout << "Сжатие в %: " << fixed << setprecision(2) << compressionRatio << " %\n" << endl;
}
