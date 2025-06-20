#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
 int voz, g;
 unsigned G;
 cout<<"Input your year of birth 0<G\n"<<"G=";
 cin>>G;
 cout<<"Input current year\n"<<"g=";
 cin>>g;
 voz=g-G;
 switch (voz)
 {case 1: case 21: case 31:case 41:case 51:case 61:case 71:case 81:case 91:case 101:cout<<"Vam "<<voz<<" god";break;
  case 2: case 3: case 4:case 22:case 23:case 24:case 32:case 33:case 34:case 42: case 43: case 44:case 52:case 53:case 54:
  case 62: case 63:case 64:case 72: case 73: case 74:case 82:case 83:case 84:case 92:case 93:case 94:cout<<"Vam "<<voz<<" goda";break;
 default: cout<<"Vam "<<voz<<" let";break;}
 return 0;
}

