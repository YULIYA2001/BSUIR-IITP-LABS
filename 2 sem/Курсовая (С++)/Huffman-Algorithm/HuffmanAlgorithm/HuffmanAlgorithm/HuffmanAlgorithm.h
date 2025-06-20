#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <iomanip> // ��� setprecision
#include <conio.h>

using namespace std;

// ���� ������
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

// ������ ��������� ��� ������������ ����
struct comparison
{
	bool operator()(Node* l, Node* r)
	{
		// ������� � ��������� ����������� ����� ���������� �������
		return l->freq > r->freq;
	}
};

Node* getNode(char ch, int freq, Node* left, Node* right);
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);
void decode(Node* root, int& index, string str);
void printTree(Node* root, unsigned k = 0);
void buildHuffmanTree(string text, int lan);

