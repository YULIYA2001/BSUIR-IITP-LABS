import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt
import SweepMethodForGeneralCond as SM_GC
import FindHWithEpsForGeneralCond as FH_GC

from scipy import linalg


def print_array(y):
    '''печать массива с 6 знаками после запятой'''
    for i in range(len(y)):
        print("{:.6f}".format(y[i]), end="  ")
    print()


def plot_test_res(y, label, X): 
    '''печать 2 графков по известным массивам и названиям'''
    fig = plt.figure()
    y2 = [np.exp(-x) + np.exp(3*x) + 0.2*np.exp(4*x) for x in X]
    plt.plot(X, y2, 'yellow', label='RealSolution')
    plt.plot(X, y, 'g:', label=label)
    plt.legend(loc='best')
    plt.show()


def plot_res(y, label, X): 
    '''печать графкa по известным массивам и названию'''
    fig = plt.figure()
    plt.plot(X, y, 'yellow', label=label)
    plt.legend(loc='best')
    plt.show()


def task3():    
    # условие y" + p*y' + q*y = f
    def p(x):
       return -0.5
    def q(x):
        return 0.5*x
    def f(x):
        return 2*x

    def al_1(left):
        return 0
    def be_1(left):
        return 1
    def al_2(right):
        return 2
    def be_2(right):
        return -1
    A = 0.5
    B = 2
    left = 1
    right = 3
    eps = 0.05


    '''
    # Тестовый пример
    def p(x):
       return -2
    def q(x):
        return -3
    def f(x):
        return np.exp(4*x)

    def al_1(left):
        return -1
    def be_1(left):
        return 1
    def al_2(right):
        return 1
    def be_2(right):
        return 1
    A = 0.6
    B = 4*np.exp(3) + np.exp(4)
    left = 0
    right = 1
    eps = 0.01
    '''


    print("Задание 3.\nМетодом конечных разностей найти приближенное решение краевой задачи  с точностью " +
        "еps = {:} и построить график. Использовать метод прогонки".format(eps))
    print("Условие:")
    print("y\" - 0,5*y' + 0,5*x*y = 2*x")
    print("left = 1   right = 3\n")

    h = 0.4
    #h = 0.1
    
    n = int((right - left) / h)
    X = np.zeros(n+1)
    for i in range(n+1):
        X[i] = left + i * h

    print("Начальный шаг: h = ", h)
    h, n, X = FH_GC.find_h(h, eps, right, left, p, q, f, n, X, al_1(left), be_1(left), al_2(right),\
       be_2(right), A, B, False)
   
    y_sweep = SM_GC.sweep_method(p, q, f, h, n, X, al_1(left), be_1(left), al_2(right), be_2(right), A, B)

    print("\nВектор-решение краевой задачи методом прогонки:")
    print_array(y_sweep)
    plot_res(y_sweep, 'Sweep method', X)
    #plot_test_res(y_sweep, 'MySolution', X)
    