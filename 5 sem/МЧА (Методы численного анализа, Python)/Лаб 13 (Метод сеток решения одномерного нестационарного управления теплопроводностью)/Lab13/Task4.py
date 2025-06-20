import numpy as np
import scipy as sp
from scipy.misc import derivative 
from scipy import sparse
from scipy import integrate
import matplotlib.pyplot as plt
'''
a = 0
b = 1
ua = lambda t: 5*t
ub = lambda t: 5*t
k = 0.2
f = lambda x: 0
phi = lambda x: 1 - x*x
h = (b - a) / 50
t = 0.5 * h*h /k
T = 0.2


a = 0
b = 1
ua = lambda t: 2
ub = lambda t: 6
k = 0.1
f = lambda x: 0
phi = lambda x: x*(1 - x)
h = (b - a) / 50
t = 0.5 * h*h /k
T = 0.5


nK = int((b - a)/h) + 1
nT = int(T/t)+1
def solve4():
    M = np.zeros(shape=(nT, nK))
    M[:,0] = np.array([ua(i) for i in np.linspace(0, T, nT)])
    M[:,-1] = np.array([ub(i) for i in np.linspace(0, T, nT)])
    M[0,:] = np.array([phi(xi) for xi in np.linspace(a, b, nK)])
    #print(M)
    for i in range(1, nT):
        for j in range(1, nK-1):
            xj = a + j*h
            M[i][j] = k * M[i-1][j+1]*t/(h*h) + \
                      (1 - 2*k*t/(h*h)) * M[i-1][j] + \
                      k*M[i-1][j-1]*t/(h*h) + \
                      t*f(xj)
    return M
matrix = solve4()
X = np.linspace(a, b, nK)

for i in range(0, nT, 50):
    plt.plot(X, matrix[i], label=i)
plt.legend()
plt.show()
'''

import numpy as np
import sympy as sp 
import matplotlib.pyplot as plt
from celluloid import Camera


def findSolution(t, h, a, b, A_, B_, T, k, f, fi):
    N = int((b - a)/h) + 1
    M = int(T / t) + 1

    M_ = np.zeros((M, N))
    X = np.linspace(a, b, N)
    
    M_[0,:] = np.array([fi(i) for i in np.linspace(a, b, N)])
    M_[:,0] = np.array([A_(i) for i in np.linspace(0, T, M)])
    M_[:,-1] = np.array([B_(i) for i in np.linspace(0, T, M)])
    for i in range(1, M):
        for j in range(1, N-1):
            M_[i][j] = t/(h*h)*k*M_[i-1][j+1] + (1 - 2*k*t/(h*h))*M_[i-1][j] + \
                t/(h*h)*k*M_[i-1][j-1] + t*f(X[j])
    
    print('a = {:}, b = {:}, Ua = {:}, Ub = {:}'.format(a, b, A_(sp.symbols('x')), B_(sp.symbols('x'))))
    print('t = {:}, h = {:}, M = {:}, N = {:}'.format(t, h, M, N))
    print('fi = {:}, k = {:}, f = {:}\nX = {:}\nMatrix:'.format(
        fi(sp.symbols('x')), k, f(sp.symbols('x')), X))
    # print matrix 
    for i in range(len(M_)):
        for j in range(len(M_[i])):
            print('{:.4f}'.format(M_[i][j]), end=' ')
        print()

    return M_, X


def task4():
    # Вариант 3
    a = 0
    b = 1
    A_ = lambda t: 2
    B_ = lambda t: 6
    T = 0.5
    k = 0.2
    def f(x):
       return 0
    def fi(x):
       return x*(1 - x)
    
    # Тестовый пример (Вариант 1)
    '''a = 0
    b = 1
    A_ = lambda t: 3
    B_ = lambda t: 0
    T = 0.5
    k = 1
    def f(x):
       return x
    def fi(x):
       return 0
    '''

    print("Задание 4.\nПромоделировать нестационарные процессы теплопроводности в зависимости от" +
         "входных данных задачи. Найти приближенное решение начально-краевой задачи для уравнения" +
         "теплопроводности")

    n = 10
    h = (b - a)/n
    t = 1/2*(h*h/k)
    Matrix, X = findSolution(t, h, a, b, A_, B_, T, k, f, fi)

    for i in range(0, len(Matrix), 2):
        plt.plot(X, Matrix[i], label='{:}t'.format(i))
    plt.legend(loc='best')
    plt.title('h = {:.4f}'.format(h))
    plt.show()

    # animation
    h2 = (b - a)/30
    t2 = 1/2*(h2*h2/k)
    Matrix2, X2 = findSolution(t2, h2, a, b, A_, B_, T, k, f, fi)
    fig = plt.figure()
    camera = Camera(fig)
    for i in range(0, len(Matrix2)):
        plt.plot(X2, Matrix2[i])
        camera.snap()
    animation = camera.animate()
    animation.save('task4.gif', writer = 'imagemagick')
    plt.title('h = {:.4f}'.format(h2))
    plt.show()