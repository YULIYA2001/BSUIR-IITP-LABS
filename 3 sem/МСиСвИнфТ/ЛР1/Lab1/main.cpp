#include <iostream>
using namespace std;

void Output(int X[20])
{
    for (int i = 0; i < 20; i++)
        cout << X[i] << ' ';
}

void Input(int X[20])
{
    for (int i = 0; i < 20; i++)
        cin >> X[i];
}

int main()
{
    setlocale (LC_ALL, "Russian");  // for Russian in console
    int A[20] = {0}, B[20] = {0}, C[20] = {0}, i, j, k;
    cout << "Введите массив A(20):\n";
    Input(A);
    cout << "Введите массив B(20):\n";
    Input(B);
    int x = 0;
    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
        {
            if(A[i] == B[j])
            {
                bool flag = 0;     // to exclude repetitions in C(20)
                for(k = 0; k < x + 1; k++)
                    if(C[k] == A[i])
                        flag = 1;
                if(flag == 0)
                {
                    C[x] = A[i];
                    x++;
                }
                break;
            }
        }
    }
    cout << "\nИсходный массив A(20): ";
    Output(A);
    cout << "\nИсходный массив B(20): ";
    Output(B);
    cout << "\nРезультирующий массив C(20): ";
    Output(C);
    return 0;
}

