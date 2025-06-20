import numpy as np

from scipy import linalg


def print_matrix(M, r):
    '''array M - матрица для печати, bool r - является ли матрица расширенной'''
    for i in range(len(M)):
        for j in range(len(M[i])): 
            if r == True and j == len(M[i]) - 1:
                print("   |   ", end='')
            print("{:+.4f}".format(M[i][j]), end='  ')          
        print()

# построение трехдиагональной матрицы
def diff_approx(p, q, f, h, n, X):
    '''fun p, q, f из дифф. уравнения 2-го порядка, float h - шаг разбиения, n - кол-во точек разбиения,
    array X - массив точек разбиения, float y0, yn - граничные значения'''
    M = np.zeros((n-1, n+1))
    V = np.zeros(n-1)

    k = 0
    for i in range(1, (n-1)+1):
        M[i-1][k] = 2 - p(X[i])*h
        M[i-1][k+1] = 2*h*h*q(X[i]) - 4
        M[i-1][k+2] = 2 + p(X[i])*h
        V[i-1] = 2 * h * h * f(X[i])
        k += 1

    rm = np.c_[M, V]

    M = np.delete(M, (0, -1), 1)
    rM = np.c_[M, V]

    #print_matrix(rM, True) 
    
    # rM - расширенная матрица - разностная схема, квадратная (rm - не квадратная)
    return rM, rm


def build_in_solve(rM, y0, yn):
    '''решение слау в виде расширенной матрицы с помощью встроенного метода'''
    V = rM[:, -1]
    M = np.delete(rM, -1, 1)

    Y = list(linalg.solve(M, V)) 
    Y.append(yn)
    Y = np.insert(Y, 0, y0)

    return Y