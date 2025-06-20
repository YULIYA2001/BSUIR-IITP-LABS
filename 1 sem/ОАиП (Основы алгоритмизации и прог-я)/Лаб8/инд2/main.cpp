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

vedomost* zapis(int &kolvo);//запись данных из файла в массив структур, рассчет ср балла
void show(vedomost *students, int kolvo);//вывод данных, хранящихся в файле
void add(vedomost *&students, int &kolvo);//добавление данных в файл
void deletion(vedomost *&students, int &kolvo);//удаление данных по  фамилии
void adjustment(vedomost *&students, int kolvo);//корректировка данных
void SearchStudent(vedomost *students, int kolvo);//абитуриенты из Минска со средним баллом не ниже 4.5


int main()
{
    setlocale(LC_ALL, "Russian");
    int kolvo;
    vedomost *students=zapis(kolvo);//запись данных из файла в массив структур, рассчет ср балла
    int variant;
    do
    {
        cout<<"\nВведите пункт меню:\n1-добавление данных\n2-удаление\n3-корректировка\n4-просмотр\n5-выход"<<endl;
        cin>>variant;
        switch (variant)
        {
            case 1: add(students, kolvo); break;//добавление данных в файл
            case 2: deletion(students, kolvo); break;//удаление данных по  фамилии
            case 3: adjustment(students, kolvo); break;//корректировка данных
            case 4: show(students, kolvo); break;//вывод данных, хранящихся в файле
            case 5: break;
            default: cout<<"Неверный пункт меню"<<endl;
        }
    }
    while (variant!=5);
    SearchStudent(students, kolvo);//абитуриенты из Минска со средним баллом не ниже 4.5
    return 0;
}

//запись данных из файла в массив структур, рассчет ср балла
 vedomost* zapis(int &kolvo)
 {
    ifstream fin;
    fin.open("InputFile.txt");
    if (!fin.is_open())
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
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

//вывод данных, хранящихся в файле
void show(vedomost *students, int kolvo)
{
    ifstream fin;
    fin.open("InputFile.txt");
    if (!fin.is_open())
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
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

//добавление данных в файл
void add(vedomost *&students, int &kolvo)
{
    vedomost *helpStudents=new vedomost[kolvo+1];//вспомогательный массив структур на 1 ячейку больше
    for (int i=0; i<kolvo; i++)
        helpStudents[i]=students[i];//заполнение ячеек нового массива старыми данными (1 ячейка остается пустая)
    delete []students;//удаление памяти старого массива
    students=helpStudents;//"увеличение" старого массива, копированием в него старых данных и пустой ячейки
    kolvo++;
    ofstream fout;
    fout.open("InputFile.txt");
    if (!fout.is_open())
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
    cout<<"Введите ФИО, адрес, отметки"<<endl;
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

//удаление данных по  фамилии
void deletion(vedomost *&students, int &kolvo)
{
    bool ind=0;
    char fam[15];
    cout<<"Введите фамилию для удаления: ";
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
    if (ind==0) cout<<"Такой фамилии нет\n";
    ofstream fout;
    fout.open("InputFile.txt");
    if (!fout.is_open())
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
    fout<<kolvo;
    for (int i=0; i<kolvo; i++)
    {
        fout<<"\n"<<students[i].surname<<" "<<students[i].name<<" "<<students[i].otchestvo<<" "<<students[i].adress<<" ";
        for (int j=0; j<3; j++)
            fout<<students[i].marks[j]<<" ";
    }
    fout.close();
}

//корректировка данных
void adjustment(vedomost *&students, int kolvo)
{
    cout<<"Введите фамилию абитуриента, чьи отметки необходимо изменить"<<endl;
    char fam[15];
    cin>>fam;
    bool ind=0;
    int sum=0, index;
    for (int i=0; i<kolvo; i++)
    {
        if (strcmp(students[i].surname, fam)==0)
        {
            cout<<"Введите новые отметки:"<<endl;
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
    if (ind==0) cout<<"Такой фамилии нет\n";
    ofstream fout;
    fout.open("InputFile.txt");
    if (!fout.is_open())
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
    fout<<kolvo;
    for (int i=0; i<kolvo; i++)
    {
        fout<<"\n"<<students[i].surname<<" "<<students[i].name<<" "<<students[i].otchestvo<<" "<<students[i].adress<<" ";
        for (int j=0; j<3; j++)
            fout<<students[i].marks[j]<<" ";
    }
    fout.close();
}

//абитуриенты из Минска со средним баллом не ниже 4.5
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
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
    fout<<kolich<<endl;
    for (int i=0; i<kolich; i++)
        fout<<result[i]<<endl;
    fout.close();
    ifstream fin;
    fin.open("OutputFile.txt");
    if (!fin.is_open())
        cout<<"Ошибка открытия файла"<<endl;
    //else cout<<"Файл открыт"<<endl;
    fin>>kolich;
    cout<<endl<<"Aбитуриенты из Минска со средним баллом не ниже 4.5"<<endl;
    for (int i=0; i<kolich; i++)
        {
            string str;
            fin>>str;
            cout<<str<<endl;
            str="";
        }
    fin.close();
}
