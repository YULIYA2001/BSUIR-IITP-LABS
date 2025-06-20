#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

struct vedomost {char surname[15];
                 char name[10];
                 char otchestvo[15];
                 char adress[15];
                 int marks[3];
                 double srMark;
                };

vedomost* zapis(int &kolvo);//������ ������ �� ����� � ������ ��������, ������� �� �����
void show(vedomost *students, int kolvo);//����� ������, ���������� � �����
void add(vedomost *&students, int &kolvo);//���������� ������ � ����
void deletion(vedomost *&students, int &kolvo);//�������� ������ ��  �������
void adjustment(vedomost *&students, int kolvo);//������������� ������
void SearchStudent(vedomost *students, int kolvo);//����������� �� ������ �� ������� ������ �� ���� 4.5


int main()
{
    setlocale(LC_ALL, "Russian");
    int kolvo;
    vedomost *students=zapis(kolvo);//������ ������ �� ����� � ������ ��������, ������� �� �����
    int variant;
    do
    {
        cout<<"\n������� ����� ����:\n1-���������� ������\n2-��������\n3-�������������\n4-��������\n5-�����"<<endl;
        cin>>variant;
        switch (variant)
        {
            case 1: add(students, kolvo); break;//���������� ������ � ����
            case 2: deletion(students, kolvo); break;//�������� ������ ��  �������
            case 3: adjustment(students, kolvo); break;//������������� ������
            case 4: show(students, kolvo); break;//����� ������, ���������� � �����
            case 5: break;
            default: cout<<"�������� ����� ����"<<endl;
        }
    }
    while (variant!=5);
    SearchStudent(students, kolvo);//����������� �� ������ �� ������� ������ �� ���� 4.5
    return 0;
}

//������ ������ �� ����� � ������ ��������, ������� �� �����
 vedomost* zapis(int &kolvo)
 {
    ifstream fin;
    fin.open("InputFile.txt");
    if (!fin.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    fin>>kolvo;
    vedomost *students=new vedomost[kolvo];
    for (int i=0; i<kolvo; i++)
    {
        fin>>students[i].surname>>students[i].name>>students[i].otchestvo>>students[i].adress;
        int sum=0;
        for (int j=0; j<3; j++)
        {
            fin>>students[i].marks[j];
            sum+=students[i].marks[j];
        }
        students[i].srMark=(double)sum/3;
    }
    fin.close();
    return students;
}

//����� ������, ���������� � �����
void show(vedomost *students, int kolvo)
{
    ifstream fin;
    fin.open("InputFile.txt");
    if (!fin.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    fin>>kolvo;
    for (int i=0; i<kolvo; i++)
    {
        fin>>students[i].surname>>students[i].name>>students[i].otchestvo>>students[i].adress;
        for (int j=0; j<3; j++)
            fin>>students[i].marks[j];
        cout<<students[i].surname<<" "<<students[i].name<<" "<<students[i].otchestvo<<" "<<students[i].adress<<" ";
        for (int j=0; j<3; j++)
            cout<<students[i].marks[j]<<" ";
        cout<<students[i].srMark;
        cout<<endl;
    }
    fin.close();
}

//���������� ������ � ����
void add(vedomost *&students, int &kolvo)
{
    vedomost *helpStudents=new vedomost[kolvo+1];//��������������� ������ �������� �� 1 ������ ������
    for (int i=0; i<kolvo; i++)
        helpStudents[i]=students[i];//���������� ����� ������ ������� ������� ������� (1 ������ �������� ������)
    delete []students;//�������� ������ ������� �������
    students=helpStudents;//"����������" ������� �������, ������������ � ���� ������ ������ � ������ ������
    kolvo++;
    ofstream fout;
    fout.open("InputFile.txt");
    if (!fout.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    cout<<"������� ���, �����, �������"<<endl;
    cin>>students[kolvo-1].surname>>students[kolvo-1].name>>students[kolvo-1].otchestvo>>students[kolvo-1].adress;
    int sum=0;
    for (int j=0; j<3; j++)
    {
        cin>>students[kolvo-1].marks[j];
        sum+=students[kolvo-1].marks[j];
    }
    students[kolvo-1].srMark=(double)sum/3;
    fout<<kolvo;
    for (int i=0; i<kolvo; i++)
    {
        fout<<"\n"<<students[i].surname<<" "<<students[i].name<<" "<<students[i].otchestvo<<" "<<students[i].adress<<" ";
        for (int j=0; j<3; j++)
        fout<<students[i].marks[j]<<" ";
    }
    fout.close();
}

//�������� ������ ��  �������
void deletion(vedomost *&students, int &kolvo)
{
    bool ind=0;
    char fam[15];
    cout<<"������� ������� ��� ��������: ";
    cin>>fam;
    for (int i=0; i<kolvo; i++)
    {
        if (strcmp(students[i].surname, fam)==0)
        {
            for (int j=i; j<kolvo-1; j++)
            {
                students[j]=students[j+1];
            }
            kolvo--;
            ind=1;
        }
    }
    if (ind==0) cout<<"����� ������� ���\n";
    ofstream fout;
    fout.open("InputFile.txt");
    if (!fout.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    fout<<kolvo;
    for (int i=0; i<kolvo; i++)
    {
        fout<<"\n"<<students[i].surname<<" "<<students[i].name<<" "<<students[i].otchestvo<<" "<<students[i].adress<<" ";
        for (int j=0; j<3; j++)
            fout<<students[i].marks[j]<<" ";
    }
    fout.close();
}

//������������� ������
void adjustment(vedomost *&students, int kolvo)
{
    cout<<"������� ������� �����������, ��� ������� ���������� ��������"<<endl;
    char fam[15];
    cin>>fam;
    bool ind=0;
    int sum=0, index;
    for (int i=0; i<kolvo; i++)
    {
        if (strcmp(students[i].surname, fam)==0)
        {
            cout<<"������� ����� �������:"<<endl;
            for (int j=0; j<3; j++)
            {
                cin>>students[i].marks[j];
                sum+=students[i].marks[j];
            }
            ind=1;
            index=i;
        }
    }
    students[index].srMark=(double)sum/3;
    if (ind==0) cout<<"����� ������� ���\n";
    ofstream fout;
    fout.open("InputFile.txt");
    if (!fout.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    fout<<kolvo;
    for (int i=0; i<kolvo; i++)
    {
        fout<<"\n"<<students[i].surname<<" "<<students[i].name<<" "<<students[i].otchestvo<<" "<<students[i].adress<<" ";
        for (int j=0; j<3; j++)
            fout<<students[i].marks[j]<<" ";
    }
    fout.close();
}

//����������� �� ������ �� ������� ������ �� ���� 4.5
void SearchStudent(vedomost *students, int kolvo)
{
    int kolich=0;
    for (int i=0; i<kolvo; i++)
    {
        if(strcmp(students[i].adress,"Minsk")==0 && students[i].srMark>4.5)
            kolich++;
    }
    char *result[kolich];
    for (int i=0, x=0; i<kolvo; i++)
    {
        if(strcmp(students[i].adress,"Minsk")==0 && students[i].srMark>4.5)
        {
            result[x]=students[i].surname;
            x++;
        }
    }
    char *helpResult;
    for (int i=1; i<kolich; i++)
        for (int j=kolich-1; j>=i; j--)
            if (result[j]>result[j-1])
                {
                    helpResult=result[j];
                    result[j]=result[j-1];
                    result[j-1]=helpResult;
                }
    ofstream fout;
    fout.open("OutputFile.txt");
    if (!fout.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    fout<<kolich<<endl;
    for (int i=0; i<kolich; i++)
        fout<<result[i]<<endl;
    fout.close();
    ifstream fin;
    fin.open("OutputFile.txt");
    if (!fin.is_open())
        cout<<"������ �������� �����"<<endl;
    //else cout<<"���� ������"<<endl;
    fin>>kolich;
    cout<<endl<<"A���������� �� ������ �� ������� ������ �� ���� 4.5"<<endl;
    for (int i=0; i<kolich; i++)
        {
            string str;
            fin>>str;
            cout<<str<<endl;
            str="";
        }
    fin.close();
}
