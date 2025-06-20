#include <locale.h>
#include "HuffmanAlgorithm.h"

// функция выбора языка
int chooseLanguage();

int main()
{
    system("chcp 1251");
    system("cls");
    char language = chooseLanguage();
    string text;
    if (language == '1')
        cout << "\nEnter a string: \n";
    else
        cout << "\nВведите строку: \n";
    getline(cin, text);
    buildHuffmanTree(text, language);
    system("pause");
    return 0;
}

int chooseLanguage()
{
    cout << "Choose language - Выберите язык" << endl;
    cout << "English - 1\nРусский - другая клавиша" << endl;
    int language = _getch();
    return language;
}
