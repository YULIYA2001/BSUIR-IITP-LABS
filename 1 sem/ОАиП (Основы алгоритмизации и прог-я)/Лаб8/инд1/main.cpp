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

void printMenu();//���� ������ ��������
void vvod(firma *people, int kolvo);//���������� ������ � ���������� �����
firma* newStruct(firma *people, int kolvo);//��������� ������ ��� �������� ���������
void show(firma *people, int kolvo);//����� ������� ������ �� �����
void dopolnenie(firma *&people, int &kolvo);//���������� ������� ������ �����������
void poiskElementa(firma  *people, int kolvo);//����� ��������� �� �������� (���� ������)
void printPoiskSurname(firma  *people, int kolvo);//����� �� �������
void printPoiskTabNum(firma  *people, int kolvo);//����� �� ���������� ������
void changeElement(firma *&people, int kolvo);//��������� ��������� �������� (����)
void changeHours(firma *&people, int kolvo);//��������� ���������� ������������ ����� �� �����
void changeTarif(firma *&people, int kolvo);//��������� ������
void deletion(firma *&people, int &kolvo);//�������� ������ �� ���������� ������
void changeSort(firma *&people, int kolvo);//���������� (�������) �������� �� �����������

int main()
{
    setlocale(LC_ALL, "Russian");
    printMenu(); //���� ������ ��������
    firma *people=0;
    int kolvo=0;
    dopolnenie(people, kolvo);
    int variantMenu;
    do
    {
        printf("\n��� ����� ����: \n");
        scanf("%d", &variantMenu);
        switch (variantMenu)
        {
            case 1: show(people, kolvo); break;//����� ������� ������ �� �����
            case 2: dopolnenie(people, kolvo); break;//���������� ������� ������ �����������
            case 3: poiskElementa(people, kolvo); break;//����� ��������� �� ��������
            case 4: changeElement(people, kolvo); break;//��������� ��������� ��������
            case 5: deletion(people, kolvo); break;//�������� ������ �� ���������� ������
            case 6: changeSort(people, kolvo); break;//���������� (�������) �������� �� �����������
            case 7: return 0;
            default: printf("�������� ����� ����\n");
        }
    }
    while (variantMenu!=7);
    return 0;
}

//���� ������ ��������
void printMenu()
{
    printf("����� ��������: \n");
    printf("1-�������� \n");
    printf("2-���������� ������ \n");
    printf("3-����� ��������� �������� � ����� ������\n");
    printf("4-��������� ��������� �������� \n");
    printf("5-�������� ������ �� ���������� ������ \n");
    printf("6-���������� �� ����������� ������� ���������� ����� \n");
    printf("7-����� \n\n\n");
}

//��������� ������ ��� �������� ���������
firma* newStruct(firma *people, int kolvo)
{
    if (kolvo==0)
        people=new firma[1];//������ ��� ���� ���������
    else
    {
        firma *helpPeople=new firma[kolvo+1];//��������������� ������ �������� �� 1 ������ ������
        for (int i=0; i<kolvo; i++)
            helpPeople[i]=people[i];//���������� ����� ������ ������� ������� ������� (1 ������ �������� ������)
        delete []people;//�������� ������ ������� �������
        people=helpPeople;//"����������" ������� �������, ������������ � ���� ������ ������ � ������ ������
    }
    return people;
}

//���������� ������ � ���������� �����
void vvod(firma *people, int kolvo)
{
    printf("�������: ");
    scanf("%s", people[kolvo].surname);
    printf("���: ");
    scanf("%s", people[kolvo].name);
    printf("��������: ");
    scanf("%s", people[kolvo].otchestvo);
    printf("��������� �����: ");
    scanf("%d", &people[kolvo].tabNum);
    printf("���������� ������������ ����� �� �����: ");
    scanf("%d", &people[kolvo].workHours);
    printf("��������� �����: ");
    scanf("%d", &people[kolvo].hourTarif);
    people[kolvo].salary=people[kolvo].workHours*people[kolvo].hourTarif;
    printf("��������: %d\n", people[kolvo].salary);
}

//����� ������� ������ �� �����
void show(firma *people, int kolvo)
{
    printf("       �������      |        ���         |      ��������      | ���. �  |   ����  |  T����  | �������� |");
    printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
    for (int i=0; i<kolvo; i++)
    {
        printf("%20s|%20s|%20s|%9d|%9d|%9d|%10d|", people[i].surname, people[i].name,
        people[i].otchestvo, people[i].tabNum, people[i].workHours, people[i].hourTarif, people[i].salary);
        printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
    }
}

//���������� ������� ������ �����������
void dopolnenie(firma *&people, int &kolvo)
{
    int YesOrNo;
    do
    {
        people=newStruct(people, kolvo);
        vvod(people, kolvo);//���������� ������ � ���������� �����
        kolvo++;
        printf("���������� ���� ������? (��: 1, ���: 0) ");
        scanf("%d", &YesOrNo);
    }
    while (YesOrNo!=0);
}

//����� ��������� �� �������� (���� ������)
void poiskElementa(firma  *people, int kolvo)
{
    printf("����� �� ����: \n�������-1\n���. �-2\n�����-3\n");
    int poisk;
    scanf("%d", &poisk);
    switch (poisk)
        {
            case 1: printPoiskSurname(people, kolvo); break;//����� �� �������
            case 2: printPoiskTabNum(people, kolvo); break;//����� �� ���������� ������
            case 3: break;
        }
}

//����� �� �������
void printPoiskSurname(firma  *people, int kolvo)
{
    bool ind=0, x=0;
    char str[30];
    printf("������� �������: ");
    scanf("%s", str);
    for (int i=0; i<kolvo; i++)
        if (strcmp(people[i].surname, str)==0)
            x=1;
    if (x==1) printf("\n\n       �������      |        ���         |      ��������      | ���. �  |   ����  |  T����  | �������� |");
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
        if (ind==0) printf("����� ������ ���\n");
}

//����� �� ���������� ������
void printPoiskTabNum(firma  *people, int kolvo)
{
    bool ind=0;
    int numb;
    printf("������� ��������� �����: ");
    scanf("%d", &numb);
    for (int i=0; i<kolvo; i++)
    {
        if (people[i].tabNum==numb)
        {
            printf("\n       �������      |        ���         |      ��������      | ���. �  |   ����  |  T����  | �������� |");
            printf("\n--------------------+--------------------+--------------------+---------+---------+---------+----------+\n");
            printf("%20s|%20s|%20s|%9d|%9d|%9d|%10d|", people[i].surname, people[i].name, people[i].otchestvo,
            people[i].tabNum, people[i].workHours, people[i].hourTarif, people[i].salary);
            ind=1;
        }
    }
    if (ind==0) printf("����� ������ ���\n");
}

//��������� ��������� �������� (����)
void changeElement(firma *&people, int kolvo)
{
    printf("��������� ����: \n���������� ������������ ����� �� �����-1\n�����-2\n�����-3\n");
    int change;
    scanf("%d", &change);
    switch (change)
        {
            case 1: changeHours(people, kolvo); break;//��������� ���������� ������������ ����� �� �����
            case 2: changeTarif(people, kolvo); break;//��������� ������
            case 3: break;
        }
}

//��������� ���������� ������������ ����� �� �����
void changeHours(firma *&people, int kolvo)
{
    bool ind=0;
    int numb1, numb2;
    printf("������� ���������� ������������ �����: ");
    scanf("%d", &numb1);
    printf("������� ����� ���������� ������������ �����: ");
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
    if (ind==0) printf("����� ������ ���\n");
}

//��������� ������
void changeTarif(firma *&people, int kolvo)
{
    bool ind=0;
    int numb1, numb2;
    printf("������� ������� �����: ");
    scanf("%d", &numb1);
    printf("������� ����� �����: ");
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
    if (ind==0) printf("����� ������ ���\n");
}

//�������� ������ �� ���������� ������
void deletion(firma *&people, int &kolvo)
{
    bool ind=0;
    int numb;
    printf("������� ��������� ����� ��� ��������: ");
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
    if (ind==0) printf("����� ������ ���\n");
}

//���������� (�������) �������� �� �����������
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
    printf("���������� ���������. ������� 1 ��� ���������. \n");
}

