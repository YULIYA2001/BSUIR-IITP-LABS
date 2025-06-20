import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt
import SweepForTask4 as SM
import FindHWithEpsForTask4 as FH

from scipy import linalg


def print_array(y):
    '''печать массива с 6 знаками после запятой'''
    for i in range(len(y)):
        print("{:.6f}".format(y[i]), end="  ")
    print()


def plot_test_res(y, label, X, y2, label2, X2): 
    '''печать 2 графков по известным массивам и названиям'''
    fig = plt.figure()
    plt.plot(X2, y2, 'b:', label=label2)
    plt.plot(X, y, 'r:', label=label)
    plt.legend(loc='best')
    plt.show()


def plot_res(y, label, X): 
    '''печать графкa по известным массивам и названию'''
    fig = plt.figure()
    plt.plot(X, y, 'b', label=label)
    plt.legend(loc='best')
    plt.show()


def find_error(h, y_sweep, k1, k2, q1, q2, f, s1, s2, mu1, mu2, a, b, c):
    '''нахождение погрешности'''
    h_prev = h * 2
    n_prev = int((b - a) / h_prev)
    X_prev = np.zeros(n_prev+1)
    for i in range(n_prev+1):
        X_prev[i] = a + i * h_prev
    y_prev = SM.sweep_method(k1, k2, q1, q2, f, s1(), s2(), mu1(), mu2(), h_prev, n_prev, X_prev, a, b, c)
    s = 0
    for i in range(len(y_prev)):
        s += (y_prev[i] - y_sweep[2*i]) * (y_prev[i] - y_sweep[2*i])
    s = np.sqrt(s/len(y_prev))
    print("s = ", s)



def task4():    
    # условие -(k(x)u')' + q(x)u = f(x)
    def k1(x):
       return 0.5
    def k2(x):
        return 1.8
    def q1(x):
       return 3.5
    def q2(x):
        return 8.2
    def f(x):
        return 10*x*(2.5 - x)

    def s1():
        return 0.5
    def s2():
        return 0.5
    def mu1():
        return 0
    def mu2():
        return 0

    a = 0
    b = 2
    c = 1.515
    eps = 0.0001


    '''
    # Тестовый пример
    def k1(x):
       return 0.4
    def k2(x):
        return 1.4
    def q1(x):
       return 3.2
    def q2(x):
        return 12
    def f(x):
        return 8*x*(2 - x**2)

    def s1():
        return 0.5
    def s2():
        return 0.5
    def mu1():
        return 0
    def mu2():
        return 0

    a = 0
    b = 1.8
    c = 1.275
    eps = 0.01
    '''



    print("Задание 4.\nМетодом баланса найти приближенное решение краевой задачи с 3 верными" +
         " значащими цифрами. Решение системы разностных уравнений найти, используя метод прогонки")
    print("Условие:")
    print("-(k(x)u')' + q(x)u = f(x)   x = (0 - 1.515 - 2)")
    print("-k(a)u'(a) + 0.5u(a) = 0")
    print("k(b)u'(b) + 0.5u(b) = 0")
    print("k = {:};  q = {:}   x = ({:}; {:})".format(k1(sp.symbols('x')), q1(sp.symbols('x')), a, c))
    print("k = {:};  q = {:}   x = ({:}; {:})".format(k2(sp.symbols('x')), q2(sp.symbols('x')), c, b))
    print("f(x) = {:}\n".format(f(sp.symbols('x'))))

    h = 0.2
    n = int((b - a) / h)
    X = np.zeros(n+1)
    for i in range(n+1):
        X[i] = a + i * h

    print("Начальный шаг: h = ", h)
    h, n, X = FH.find_h(k1, k2, q1, q2, f, s1(), s2(), mu1(), mu2(), h, n, X, a, b, c, eps, False)
   
    y_sweep = SM.sweep_method(k1, k2, q1, q2, f, s1(), s2(), mu1(), mu2(), h, n, X, a, b, c)

    # погрешность
    #find_error(h, y_sweep, k1, k2, q1, q2, f, s1, s2, mu1, mu2, a, b, c)

    #print("\nВектор-решение краевой задачи методом прогонки:")
    #print_array(y_sweep)
    plot_res(y_sweep, 'Sweep method', X)
