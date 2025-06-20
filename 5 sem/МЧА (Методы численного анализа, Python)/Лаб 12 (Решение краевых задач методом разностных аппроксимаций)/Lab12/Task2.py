import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt
import DifferenceApproximationMethod as DAM
import SweepMethod as SM
import FindHWithEps as FH

from scipy import linalg


def print_array(y):
    '''печать массива с 6 знаками после запятой'''
    for i in range(len(y)):
        print("{:.6f}".format(y[i]), end="  ")
    print()


def plot_res(y, label, X): 
    '''печать графкa по известным массивам и названию'''
    fig = plt.figure()
    plt.plot(X, y, 'yellow', label=label)
    plt.legend(loc='best')
    plt.show()


def task2():
    left = 0
    right = 1
    eps = 0.03
    y0 = 4
    yn = 0

    # условие y" + p*y' + q*y = f
    def p(x):
       return np.exp(-(x*x + 1))

    def q(x):
        return 10 * (1 + np.exp(-x))

    def f(x):
        return np.exp(5/2 * x) * (1/2 + x)

    print("Задание 2.\nНайти приближенное решение краевой задачи методом конечных разностей с точностью " +
        "еps = {:} и построить его график".format(eps))
    print("Условие:")
    print("y\" + exp(-(x*x + 1))*y' + 10 * (1 + exp(-x))*y = exp(5/2 * x) * (1/2 + x)")
    print("y0 = 4   yn = 0  \nleft = 0   right = 1\n")

    h = 0.5
    print("Начальный шаг: h = ", h)
    h, n, X = FH.find_h(h, right, left, p, q, f, y0, yn, eps, True)

    # rM - расширенная матрица (разностная схема, квадратная), rm - (не квадратная)
    rM, rm = DAM.diff_approx(p, q, f, h, n, X)
    print("\nМатрица системы уравнений")
    DAM.print_matrix(rm, True)
    y_sweep = SM.sweep_method_for_diff(p, q, f, h, n, X, y0, yn, True)
    print("\nВектор-решение краевой задачи методом прогонки:")
    print_array(y_sweep)
    plot_res(y_sweep, 'Sweep method', X)
