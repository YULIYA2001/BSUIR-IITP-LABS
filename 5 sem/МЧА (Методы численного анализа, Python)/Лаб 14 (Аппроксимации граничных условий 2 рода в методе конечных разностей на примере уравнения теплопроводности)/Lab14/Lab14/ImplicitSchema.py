import math
import numpy as np
import sympy as sp 
import PrintMatrix as PM


def implicit(t, h, a, b, g1, g2, T, k, f, fi, gy, print_res):
    N = int((b - a)/h) + 1
    M = math.ceil(T / t) + 1

    M_ = np.zeros((M, N))
    X = np.linspace(a, b, N)

    M_[0,:] = np.array([fi(i) for i in np.linspace(a, b, N)])
    M_[:,0] = np.array([g1(i) for i in np.linspace(0, T, M)])
    
    for i in range(1, M):
        M2 = np.zeros(shape=(N-2, N-2))
        Y = np.zeros(N-2)
        M2[0][0] = -(1 + 2*t*k / (h*h))
        M2[0][1] = t*k / (h*h)

        Y[0] = -(M_[i-1][1] + t*f(1,i*t) + t*k/(h*h) * g1(i*t))

        for j in range(1, N-3):
            M2[j][j-1] = t*k / (h*h)
            M2[j][j] = -(1 + 2*t*k / (h*h))
            M2[j][j+1] = t*k / (h*h)
            Y[j] = -(M_[i-1][j+1] + t*f(X[j], i*t))

        if (gy == 1):
            M2[-1][-1] = -(1 + t*k/(h*h))
            M2[-1][-2] = t*k/(h*h)
            Y[-1] = -(M_[i-1][-2] + t*f(X[-2], i*t) + t*k/(h*h) * h*g2(i*t))
        elif (gy == 2):
            M2[-1][-1] = -(1 + 2*t*k/(h*h))
            M2[-1][-2] = 2*t*k/(h*h)
            Y[-1] = -(M_[i-1][-2] + t*f(X[-2], i*t) + 2*t*k/(h*h) * h*g2(i*t))
        else:
            print("Wrong gy")
            exit()
        

        res = list(np.linalg.solve(M2, Y))
        if (gy == 1):
            res.append(res[-1] + h*g2(i*t))
        else:
            res.append(res[-2] + 2*h*g2(i*t))

        #print('\n\nres \n', res)

        M_[i, 1:] = res
        
        #print('\n\nM2 \n', M2)
        #print('\n\nY \n', Y)
    
    if (print_res):
        print('t = {:}, h = {:}, M = {:}, N = {:}'.format(t, h, M, N))
        print('fi = {:}, k = {:}, f = {:}\nX = {:}\nMatrix:'.format(
            fi(sp.symbols('x')), k, f(sp.symbols('x'), sp.symbols('t')), X))
        PM.print_matrix(M_)
    return M_, X
