import numpy as np


def print_array(y):
    '''печать массива с 4 знаками после запятой'''
    for i in range(len(y)):
        print("{:.4f}".format(y[i]), end="  ")
    print()


# метод прогонки для дифференциального уравнения
def sweep_method_for_diff(p, q, f_, h, n, X, y0, yn, need_print):
    '''fun p, q, f из дифф. уравнения 2-го порядка, float h - шаг разбиения, n - кол-во точек разбиения, array
    X - массив точек разбиения, float y0, yn - граничные значения, bool need_print - печатать ли коэффициенты'''
    a = np.zeros(n-1)
    b = np.zeros(n-1)
    c = np.zeros(n-1)
    f = np.zeros(n-1)

    for i in range(n-1):
        a[i] = 2 - p(X[i+1])*h
        b[i] = 2*h*h*q(X[i+1]) - 4
        c[i] = 2 + p(X[i+1])*h
        f[i] = 2 * h * h * f_(X[i+1])

    if need_print == True:
        # для Task2 надо обязательно
        print("\nКоэффициенты матрицы системы и правой части")
        print("a = ", end=' ')
        print_array(a)
        print("\nb = ", end=' ')
        print_array(b)
        print("\nc = ", end=' ')
        print_array(c)
        print("\nf = ", end=' ')
        print_array(f)
    
    L = np.zeros(n)
    K = np.zeros(n)
    K[0] = y0

    for i in range(1, n):
        L[i] = -c[i-1] / (b[i-1] + a[i-1]*L[i-1])
        K[i] = (f[i-1] - a[i-1]*K[i-1]) / (b[i-1] + a[i-1]*L[i-1])

    #print("L = ", L)
    #print("K = ", K)

    y = np.zeros(n+1)
    y[-1] = yn
    y[0] = y0
    for i in range(len(y)-2, -1, -1):
        y[i] = L[i]*y[i+1] + K[i]
    
    #print("y = ", y)

    return y