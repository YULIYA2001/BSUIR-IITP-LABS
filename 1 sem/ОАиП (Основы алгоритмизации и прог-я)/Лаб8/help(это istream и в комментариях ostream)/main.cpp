#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
    setlocale(LC_ALL, "Russian");

    string path="MyFile.txt";
    /*ofstream fout;
    fout.open(path, ofstream::app);
    if (!fout.is_open())
        cout<<"������ �������� �����"<<endl;
    else
    {
        cout<<"������ �����"<<endl;
        int a;
        cin>>a;
        fout<<a<<"\n";
    }
    fout.close();*/
    ifstream fin;
    fin.open(path);
    if (!fin.is_open())
        cout<<"������ �������� �����"<<endl;
    else
    {
        cout<<"���� ������"<<endl;
        string ch;
        while (!fin.eof())
        {
            ch="";
            getline(fin, ch);//
            //fin>>ch;
            cout<<ch<<endl;
        }
    }
    fin.close();
    return 0;
}
