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


def plot_res(y1, y2, label1, label2, X): 
    '''печать 2 графков по известным массивам и названиям'''
    fig = plt.figure()
    plt.plot(X, y1, 'yellow', label=label1)
    plt.plot(X, y2, 'r:', label=label2)
    plt.legend(loc='best')
    plt.show()


def task1():
    # k -  вариант
    k = 3
    a = np.sin(k)
    b = np.cos(k)
    left = -1
    right = 1
    eps = 0.001
    y0 = yn = 0

    # условие y" + p*y' + q*y = f
    def p(x):
       return 0

    def q(x):
        return (1 + b*x**2)/a

    def f(x):
        return -1/a

    print("Задание 1.\nСоставить разностную схему и получить численное решение краевой задачи с точностью еps =", eps)
    print("Условие:")
    print("sin({0}) * y\" + (1 + cos({0}) * x**2)*y = -1".format(k))
    print("y0 = yn = 0,  left = -1,   right = 1\n")

    h = 0.4
    print("Начальный шаг: h = ", h)
    h, n, X = FH.find_h(h, right, left, p, q, f, y0, yn, eps, False)

    # rM - расширенная матрица (разностная схема, квадратная), rm - (не квадратная)
    rM, rm = DAM.diff_approx(p, q, f, h, n, X)
    #DAM.print_matrix(rM, True)
    y_build = DAM.build_in_solve(rM, y0, yn)
    y_sweep = SM.sweep_method_for_diff(p, q, f, h, n, X, y0, yn, False)
    print("\nВектор-решение краевой задачи встроенным методом:")
    print_array(y_build)
    print("\nВектор-решение краевой задачи методом прогонки:")
    print_array(y_sweep)
    plot_res(y_build, y_sweep, 'Build in method', 'Sweep method', X)
    