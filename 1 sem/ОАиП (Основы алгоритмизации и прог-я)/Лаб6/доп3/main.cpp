#include <iostream>
#include <string.h>

using namespace std;

void povtor(char *copyword, char *word, int len, int *povt);
int fact(int a);

int main()
{
    setlocale(LC_ALL, "Russian");
    char word[15];
    cout<<"Введите слово: "<<endl;
    cin>>word;
    char copyword[15];
    strcpy(copyword, word);
    int len=strlen(word);
    int *povt=new int[7]{};
    povtor(copyword, word, len, povt);
    int factNiz=1;
    for (int i=0; i<7; i++)
    {
        if (povt[i])
            factNiz*=fact(povt[i]);
    }
    cout<<"Количество различных анаграмм: "<<(fact(len)/factNiz);
    delete []povt;
    return 0;
}

void povtor(char *copyword, char *word, int len, int *povt)
{
    int k, x=0;
    for (int i=0; i<len-1; i++)
    {
        k=1;
        for (int j=i+1; j<len; j++)
             {
                 if(word[i]==copyword[j])
                 {
                     copyword[j]=0;
                     k++;
                 }
             }
        if (k!=0&&k!=1)
        {
            povt[x]=k;
            x++;
        }
    }
}

int fact(int a)
{
    if (a==1||a==0)
        return 1;
    else return fact(a-1)*a;
}
