import numpy as np 
import SweepMethod as SM
import matplotlib.pyplot as plt


def print_array(y):
    '''печать массива с 6 знаками после запятой'''
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


def find_h(h, right, left, p, q, f, y0, yn, eps, need_print):
    '''Нахождение шага h, кол-ва разбиений отрезка n и массива точек X, необходимых для заданной точности eps
    bool need_print - надо ли печатать промежуточные решения у'''
    # steps - кол-во раз уменьшения шага h вдвое
    steps = 0
    s = 1000
    n, X = find_n_X(h, right, left)
    while s > eps:
        n_next, X_next = find_n_X(h/2, right, left)

        y = SM.sweep_method_for_diff(p, q, f, h, n, X, y0, yn, False)
        y_next = SM.sweep_method_for_diff(p, q, f, h/2, n_next, X_next, y0, yn, False)
        #plot_res(y, y_next, 'y', 'y_next', X, X_next)

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
    