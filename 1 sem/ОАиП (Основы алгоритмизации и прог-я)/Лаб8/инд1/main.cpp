#include <iostream>
#include <stdio.h>
#include <string.h>

//using namespace std;

struct firma {char surname[30];
              char name[15];
              char otchestvo[20];
              int tabNum;
              int workHours;
              int hourTarif;
              int salary;
             };

void printMenu();//меню выбора действия
void vvod(firma *people, int kolvo);//заполнение данных о работниках фирмы
firma* newStruct(firma *people, int kolvo);//выделение памяти под элементы структуры
void show(firma *people, int kolvo);//вывод таблицы данных на экран
void dopolnenie(firma *&people, int &kolvo);//дополнение таблицы новыми работниками
void poiskElementa(firma  *people, int kolvo);//поиск работника по элементу (меню поиска)
void printPoiskSurname(firma  *people, int kolvo);//поиск по Фамилии
void printPoiskTabNum(firma  *people, int kolvo);//поиск по Табельному номеру
void changeElement(firma *&people, int kolvo);//изменение заданного элемента (меню)
void changeHours(firma *&people, int kolvo);//изменение количества отработанных часов за месяц
void changeTarif(firma *&people, int kolvo);//изменение тарифа
void deletion(firma *&people, int &kolvo);//удаление данных по табельному номеру
void changeSort(firma *&people, int kolvo);//сортировка (обменом) зарплаты по возрастанию

int main()
{
    setlocale(LC_ALL, "Russian");
    printMenu(); //меню выбора действия
    firma *people=0;
    int kolvo=0;
    dopolnenie(people, kolvo);
    int variantMenu;
    do
    {
        printf("\nВаш пункт меню: \n");
        scanf("%d", &variantMenu);
        switch (variantMenu)
        {
            case 1: show(people, kolvo); break;//вывод таблицы данных на экран
            case 2: dopolnenie(people, kolvo); break;//дополнение таблицы новыми работниками
            case 3: poiskElementa(people, kolvo); break;//поиск работника по элементу
            case 4: changeElement(people, kolvo); break;//изменение заданного элемента
            case 5: deletion(people, kolvo); break;//удаление данных по табельному номеру
            case 6: changeSort(people, kolvo); break;//сортировка (обменом) зарплаты по возрастанию
            case 7: return 0;
            default: printf("Неверный пункт меню\n");
        }
    }
    while (variantMenu!=7);
    return 0;
}

//меню выбора действия
void printMenu()
{
    printf("Выбор действия: \n");
    printf("1-просмотр \n");
    printf("2-дополнение данных \n");
    printf("3-поиск заданного элемента и вывод данных\n");
    printf("4-изменение заданного элемента \n");
    printf("5-удаление данных по табельному номеру \n");
    printf("6-сортировка по возрастанию размера заработной платы \n");
    printf("7-выход \n\n\n");
}

//выделение памяти под элементы структуры
firma* newStruct(firma *people, int kolvo)
{
    if (kolvo==0)
        people=new firma[1];//память под одну структуру
    else
    {
        firma *helpPeople=new firma[kolvo+1];//вспомогательный массив структур на 1 ячейку больше
        for (int i=0; i<kolvo; i++)
            helpPeople[i]=people[i];//заполнение ячеек нового массива старыми данными (1 ячейка остается пустая)
        delete []people;//удаление памяти старого массива
        people=helpPeople;//"увеличение" старого массива, копированием в него старых данных и пустой ячейки
    }
    return people;
}

//заполнение данных о работниках фирмы
void vvod(firma *people, int kolvo)
{
    printf("Фамилия: ");
    scanf("%s", people[kolvo].surname);
    printf("Имя: ");
    scanf("%s", people[kolvo].name);
    printf("Отчество: ");
    scanf("%s", people[kolvo].otchestvo);
    printf("Табельный номер: ");
    scanf("%d", &people[kolvo].tabNum);
    printf("Количество отработанных часов за месяц: ");
    scanf("%d", &people[kolvo].workHours);
    printf("Почасовой тариф: ");
    scanf("%d", &people[kolvo].hourTarif);
    people[kolvo].salary=people[kolvo].workHours*people[kolvo].hourTarif;
    printf("Зарплата: %d\n", people[kolvo].salary);
}

//вывод таблицы данных на экран
void show(firma *people, int kolvo)
{
    printf("       Фамилия      |        Имя         |      Отчество      | Таб. №  |   Часы  |  Tариф  | Зарплата |");
    printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
    for (int i=0; i<kolvo; i++)
    {
        printf("%20s|%20s|%20s|%9d|%9d|%9d|%10d|", people[i].surname, people[i].name,
        people[i].otchestvo, people[i].tabNum, people[i].workHours, people[i].hourTarif, people[i].salary);
        printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
    }
}

//дополнение таблицы новыми работниками
void dopolnenie(firma *&people, int &kolvo)
{
    int YesOrNo;
    do
    {
        people=newStruct(people, kolvo);
        vvod(people, kolvo);//заполнение данных о работниках фирмы
        kolvo++;
        printf("Продолжить ввод данных? (да: 1, нет: 0) ");
        scanf("%d", &YesOrNo);
    }
    while (YesOrNo!=0);
}

//поиск работника по элементу (меню поиска)
void poiskElementa(firma  *people, int kolvo)
{
    printf("Поиск по полю: \nФамилия-1\nТаб. №-2\nВыход-3\n");
    int poisk;
    scanf("%d", &poisk);
    switch (poisk)
        {
            case 1: printPoiskSurname(people, kolvo); break;//поиск по Фамилии
            case 2: printPoiskTabNum(people, kolvo); break;//поиск по Табельному номеру
            case 3: break;
        }
}

//поиск по Фамилии
void printPoiskSurname(firma  *people, int kolvo)
{
    bool ind=0, x=0;
    char str[30];
    printf("Введите фамилию: ");
    scanf("%s", str);
    for (int i=0; i<kolvo; i++)
        if (strcmp(people[i].surname, str)==0)
            x=1;
    if (x==1) printf("\n\n       Фамилия      |        Имя         |      Отчество      | Таб. №  |   Часы  |  Tариф  | Зарплата |");
    for (int i=0; i<kolvo; i++)
    {
        if (strcmp(people[i].surname, str)==0)
        {
            printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
            printf("%20s|%20s|%20s|%9d|%9d|%9d|%10d|", people[i].surname, people[i].name, people[i].otchestvo,
            people[i].tabNum, people[i].workHours, people[i].hourTarif, people[i].salary);
            ind=1;
        }
    }
        if (ind==0) printf("Таких данных нет\n");
}

//поиск по Табельному номеру
void printPoiskTabNum(firma  *people, int kolvo)
{
    bool ind=0;
    int numb;
    printf("Введите табельный номер: ");
    scanf("%d", &numb);
    for (int i=0; i<kolvo; i++)
    {
        if (people[i].tabNum==numb)
        {
            printf("\n       Фамилия      |        Имя         |      Отчество      | Таб. №  |   Часы  |  Tариф  | Зарплата |");
            printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
            printf("%20s|%20s|%20s|%9d|%9d|%9d|%10d|", people[i].surname, people[i].name, people[i].otchestvo,
            people[i].tabNum, people[i].workHours, people[i].hourTarif, people[i].salary);
            ind=1;
        }
    }
    if (ind==0) printf("Таких данных нет\n");
}

//изменение заданного элемента (меню)
void changeElement(firma *&people, int kolvo)
{
    printf("Изменение поля: \nКоличество отработанных часов за месяц-1\nТариф-2\nВыход-3\n");
    int change;
    scanf("%d", &change);
    switch (change)
        {
            case 1: changeHours(people, kolvo); break;//изменение количества отработанных часов за месяц
            case 2: changeTarif(people, kolvo); break;//изменение тарифа
            case 3: break;
        }
}

//изменение количества отработанных часов за месяц
void changeHours(firma *&people, int kolvo)
{
    bool ind=0;
    int numb1, numb2;
    printf("Введите количество отработанных часов: ");
    scanf("%d", &numb1);
    printf("Введите новое количество отработанных часов: ");
    scanf("%d", &numb2);
    for (int i=0; i<kolvo; i++)
    {
        if (people[i].workHours==numb1)
        {
            people[i].workHours=numb2;
            people[i].salary=people[i].workHours*people[i].hourTarif;
            ind=1;
        }
    }
    if (ind==0) printf("Таких данных нет\n");
}

//изменение тарифа
void changeTarif(firma *&people, int kolvo)
{
    bool ind=0;
    int numb1, numb2;
    printf("Введите искомый тариф: ");
    scanf("%d", &numb1);
    printf("Введите новый тариф: ");
    scanf("%d", &numb2);
    for (int i=0; i<kolvo; i++)
    {
        if (people[i].hourTarif==numb1)
        {
            people[i].hourTarif=numb2;
            people[i].salary=people[i].workHours*people[i].hourTarif;
            ind=1;
        }
    }
    if (ind==0) printf("Таких данных нет\n");
}

//удаление данных по табельному номеру
void deletion(firma *&people, int &kolvo)
{
    bool ind=0;
    int numb;
    printf("Введите табельный номер для удаления: ");
    scanf("%d", &numb);
    for (int i=0; i<kolvo; i++)
    {
        if (people[i].tabNum==numb)
        {
            for (int j=i; j<kolvo-1; j++)
            {
                people[j]=people[j+1];
            }
            kolvo--;
            ind=1;
        }
    }
    if (ind==0) printf("Таких данных нет\n");
}

//сортировка (обменом) зарплаты по возрастанию
void changeSort(firma *&people, int kolvo)
{
    firma *helpPeople=new firma[1];
    for (int i=1; i<kolvo; i++)
        for (int j=kolvo-1; j>=i; j--)
            if (people[j].salary<people[j-1].salary)
                {
                    helpPeople[0]=people[j];
                    people[j]=people[j-1];
                    people[j-1]=helpPeople[0];
                }
    delete []helpPeople;
    printf("Сортировка выполнена. Нажмите 1 для просмотра. \n");
}

