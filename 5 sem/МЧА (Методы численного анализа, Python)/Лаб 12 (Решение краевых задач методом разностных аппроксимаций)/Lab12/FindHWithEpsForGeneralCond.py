import numpy as np 
import SweepMethodForGeneralCond as SM_GC
import matplotlib.pyplot as plt


def print_array(y):
    '''печать массива с 4 знаками после запятой'''
    for i in range(len(y)):
        print("{:.4f}".format(y[i]), end="  ")
    print()


def find_n_X(h, right, left):
    '''Нахождение массива Х и кол-ва точек разбиения n по заданному шагу h'''
    n = int((right - left) / h)
    X = np.zeros(n+1)
    for i in range(n+1):
        X[i] = left + i * h
    return n, X


def plot_res(y1, y2, label1, label2, X1, X2): 
    '''Отрисовка 2 графиков по заданным массивам точек X и y'''
    fig = plt.figure()
    plt.plot(X1, y1, 'yellow', label=label1)
    plt.plot(X2, y2, 'r:', label=label2)
    plt.legend(loc='best')
    plt.show()


def find_h(h, eps, right, left, p, q, f, n, X, al_1, be_1, al_2, be_2, A, B, need_print):
    '''Нахождение шага h, кол-ва разбиений отрезка n и массива точек X, необходимых для заданной точности eps
    bool need_print - надо ли печатать промежуточные решения у
    p, q, f_, - функции от х в условии дифф уравнения
    right, left, - границы отрезка
    al_1, be_1, al_2, be_2, - функции из обобщенных граничных условий, 
    A, B - числа из обобщенных граничных услови'''

    # steps - кол-во раз уменьшения шага h вдвое
    steps = 0
    s = 1000
    n, X = find_n_X(h, right, left)
    # шаг уменьшать вдвое, пока не достигнута точность (разность с предыдущим и след шагом >eps) 
    while s > eps:
        n_next, X_next = find_n_X(h/2, right, left)

        y = SM_GC.sweep_method(p, q, f, h, n, X, al_1, be_1, al_2, be_2, A, B)
        y_next = SM_GC.sweep_method(p, q, f, h/2, n_next, X_next, al_1, be_1, al_2, be_2, A, B)
        plot_res(y, y_next, 'y, h = {:}'.format(h), 'y_next, h = {:}'.format(h/2), X, X_next)

        s = 0
        for i in range(len(y)):
            s += (y[i] - y_next[2*i]) * (y[i] - y_next[2*i])
        s = np.sqrt(s/len(y))
        h, n, X = h/2, n_next, X_next
        steps += 1
        if need_print == True:
            # for Task2
            print("\ny = ", end=' ')
            print_array(y)
            print("y_next = ", end=' ')
            print_array(y_next)
            print("s = ", s)
    
    print("\nh = ", h)
    print("n = ", n)
    print("steps = ", steps)
    print("s = ", s)

    return h, n, X

