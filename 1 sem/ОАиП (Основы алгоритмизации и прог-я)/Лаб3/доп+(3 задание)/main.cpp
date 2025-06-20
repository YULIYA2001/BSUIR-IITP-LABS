#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
    setlocale (LC_ALL, "Russian");
    cout<<"¬ведите натуральное число k=";
    int k;
    cin>>k;
    int i=1, s=0;
    for( ; s<k; i++){
       int x=i*i, t=0;
       while (x>0){
           t++;
           x/=10;
       }
       s+=t;
    }
    i--;
    i*=i;
    for(int j=1; j<=s-k; j++, i/=10);
    cout << i%10;
    //cout<<k<<"-€ цифра последовательности "<<a;
    getch();
    return 0;
}
