#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main ()
{
    setlocale(LC_ALL, "Russian");

    string path="MyFile.txt";

    fstream fs;
    fs.open(path, fstream::in | fstream::out | fstream::app);
    if (!fs.is_open())
        cout<<"������ �������� �����"<<endl;
    else
    {
        string n;
        cout<<"1-������, 2-������"<<endl;
        int a;
        cin>>a;
        if (a==1)
        {
            SetConsoleCP(1251);
            cin>>n;
            fs<<n<<"\n";
            SetConsoleCP(866);
        }
        if (a==2)
        {
            while (!fs.eof())
            {
                n="";
                getline(fs, n);
                //fs>>n;
                cout<<n<<endl;
            }
        }
    }
    fs.close();
    return 0;
}

