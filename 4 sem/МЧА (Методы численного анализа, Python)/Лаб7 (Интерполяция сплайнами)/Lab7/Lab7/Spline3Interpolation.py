import numpy as np
import SweepMethod as SM 

def spline_method(xi, yi, n, x, h):
    ''' Метод для интерполирования кубическими сплайнами (по массивам точек xi, yi) и
        вычисления значения сплайна в точке х. n -количество отрезков, h - равномерный шаг'''
    a = np.zeros(n)
    for i in range(n):
        a[i] = yi[i]

    A = np.zeros((n-1, n-1+1))
    A[0][0] = 4*h
    A[0][1] = h
    for i in range(1, n-1):
        A[i][i-1] = h
        A[i][i] = 4*h
        A[i][i+1] = h
    #print(A)

    # обрезка лишних строк и столбцов матрицы
    A = A[:, :-1]
    #print(A)

    B = np.zeros(n-1)
    for i in range(1, n):
        B[i - 1] = 3*(yi[i+1] - 2*yi[i] + yi[i-1])/h
    #print(B)

    #c = np.linalg.solve(A, B)
    c = SM.sweep_method(A, B, n-1)
    c = np.insert(c, 0, 0)
    c = np.append(c, 0)
    #print("c: ", c)
    
    b = np.zeros(n)
    for i in range(n):
        b[i] = (yi[i+1] - yi[i])/h - h*(c[i+1] + 2*c[i])/3
    #print("b: ", b)
    
    d = np.zeros(n)
    for i in range(n):
        d[i] = (c[i+1] - c[i])/(3*h)
    #print("d: ", d)

    # дополнение коэффициентов до размера n
    a = np.append(a, yi[n])
    b = np.append(b, b[n-1] + 2*c[n-1]*h + 3*d[n-1]*h**2)
    d = np.append(d, d[n-1])

    #print("\nКоэффициенты сплайна: ")
    #print("a: ", a)
    #print("b: ", b)
    #print("c: ", c)
    #print("d: ", d)

    # найдем номер отрезка i
    i = int((x - xi[0])/h)
    S = a[i] + b[i]*(x-xi[i]) + c[i]*((x-xi[i])**2) + d[i]*((x-xi[i])**3)

    return S
