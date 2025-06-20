#include <iostream>

using namespace std;

int length(string n2);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout<<"¬ведите пр€мой код в 8-битном представлении: ";
    string n2;
    cin>>n2;
    int len=length(n2);
    if (n2[0]=='1')
        for (int i=1; i<len; i++)
        {
            if (n2[i]=='1')
                n2[i]='0';
            else
            {
                if (n2[i]=='0')
                n2[i]='1';
            }
        }
    cout<<"ќбратный код в 8-битном представлении: "<<n2;
    return 0;
}

int length(string n2)
{
    int length=0, i=0;
    while (n2[i]!='\0')
    {
        length+=1;
        i++;
    }
    return length;
}

/*switch (length(n2))
    {
        case 1: n2="0000000"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        case 2: n2="000000"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        case 3: n2="00000"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        case 4: n2="0000"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        case 5: n2="000"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        case 6: n2="00"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        case 7: n2="0"+n2; cout<<"ѕр€мой код в 8-битном представлении: "<<n2<<endl; break;
        default: cout<<"Ќевозможно представить в 8-битном представлении"<<endl;
    }
    */
