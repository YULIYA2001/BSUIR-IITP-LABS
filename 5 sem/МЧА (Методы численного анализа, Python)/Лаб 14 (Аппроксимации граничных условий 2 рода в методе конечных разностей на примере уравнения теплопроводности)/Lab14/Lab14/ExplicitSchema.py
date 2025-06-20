import math
import numpy as np
import sympy as sp 
import PrintMatrix as PM


def explicit(t, h, a, b, g1, g2, T, k, f, fi, gy, print_res):
    N = int((b - a)/h) + 1
    M = math.ceil(T / t) + 1

    M_ = np.zeros((M, N))
    X = np.linspace(a, b, N)
    
    M_[0,:] = np.array([fi(i) for i in np.linspace(a, b, N)])
    M_[:,0] = np.array([g1(i) for i in np.linspace(0, T, M)])

    for i in range(1, M):
        for j in range(1, N-1):
            M_[i][j] = k*t/(h*h) * M_[i-1][j-1] + (1 - 2*k*t/(h*h)) * M_[i-1][j] + \
                k*t/(h*h) * M_[i-1][j+1] + t*f(X[j], i*t)
        if (gy == 1):
            M_[i][-1] = h*g2(i*t) + M_[i][-2]
        elif (gy == 2):
            M_[i][-1] = M_[i][-3] + 2 * h * g2(t * i)
        else:
            print("Wrong gy")
            exit()

    if (print_res):
        print('t = {:}, h = {:}, M = {:}, N = {:}'.format(t, h, M, N))
        print('fi = {:}, k = {:}, f = {:}\nX = {:}\nMatrix:'.format(
            fi(sp.symbols('x')), k, f(sp.symbols('x'), sp.symbols('t')), X))
        PM.print_matrix(M_)
    return M_, X

