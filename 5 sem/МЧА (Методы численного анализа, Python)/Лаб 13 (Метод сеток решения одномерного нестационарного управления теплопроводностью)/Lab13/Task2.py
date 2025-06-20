import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt, matplotlib.pylab


def print_array(y):
    '''печать массива с 6 знаками после запятой'''
    for i in range(len(y)):
        print("{:.6f}".format(y[i]), end="  ")
    print()

def plot_res(n, X, y, label, title): 
    '''печать n графков по известным массивам и названиям, y - двумерный массив, X, label - одномерные,
        n - размерность label, X и первая размерность y'''
    fig = plt.figure()
    for i in range(n):
        plt.plot(X, y[i], label=label[i])
    plt.legend(loc='best')
    plt.title(title)
    plt.show()


def plot_res_pro(n, X, y, label, title):
    '''печать n графков на 2 сист. координат(пополам) по известным массивам и названиям, 
        y - двумерный массив, X, label - одномерные,
        n - размерность label, X и первая размерность y'''
    plt.figure()
    ax1 = plt.subplot(1,2,1)
    ax2 = plt.subplot(1,2,2)
    plt.sca(ax1)
    for i in range(int(n/2)):
        plt.plot(X, y[i], label=label[i])
    plt.legend(loc='best')

    plt.sca(ax2)
    for i in range(int(n/2), n):
        plt.plot(X, y[i], label=label[i])
    plt.legend(loc='best')
    plt.title(title)
    plt.show()

def findSolution(k, f, h, n, X, A_, B_, a_, b_, c1, c2, x0, C):
    '''метод прогонки для решения стационарного уравнения теплопроводности методом баланса (2k -> 1 точка разб.)
        с гр. усл. 1 рода ( u(a) = Ua ) 
        k - массив из 3 const
        f, - функция от х в условии дифф уравнения
        h, n, X, - шаг, кол-во разбиений отрезка, массив точек разбиения
        A_, B_ - из граничных условий, 
        a_, b_, c1, c2 - границы отрезка и точки третьих частей отрезка
        x0 - массив, 1 или 2 точки расположения источников тепла
        С - массив, мощность источника тепла (соотв х0 1 или 2 значения)'''

    # массивы для коэффициентов трехдиагональной матрицы
    a = np.zeros(n-1)
    b = np.zeros(n-1)
    c = np.zeros(n-1)
    d = np.zeros(n-1)

    # коэффициенты трехдиагональной матрицы
    # a = coef_a, b = -(coef_a+coef_b), c = coef_b, d = -f(x)*h^2
    def coef_a(x, k1, k2, k3, c1, c2):
        if x < c1:
            return k1
        elif x-h < c1 < x:
            return h / ((c1 - x + h) / k1 + (x - c1) / k2)
        elif x <= c2:
            return k2
        elif x-h < c2 < x:
            return h / ((c2 - x + h) / k2 + (x - c2) / k3)
        else:
            return k3
    
    def coef_b(x, k1, k2, k3, c1, c2):
        if x < c1:
            return k1
        elif x < c1 < x+h:
            return h / ((c1 - x) / k1 + (x+h - c1) / k2)
        elif x+h <= c2:
            return k2
        elif x < c2 < x+h:
            return h / ((c2 - x) / k2 + (x+h - c2) / k3)
        else:
            return k3

    for i in range(n-1):
        a[i] = coef_a(X[i], k[0], k[1], k[2], c1, c2)
        b[i] = -(coef_a(X[i], k[0], k[1], k[2], c1, c2) + coef_b(X[i], k[0], k[1], k[2], c1, c2))
        c[i] = coef_b(X[i], k[0], k[1], k[2], c1, c2)
        sum = 0
        for j in range(len(x0)):
            sum += f(X[i], x0[j], C[j])
        d[i] = - h * sum

    # подстановка у0 и уn из граничных условий
    d[0] -= a[0] * A_
    d[-1] -= c[-1] * B_

    # сам метод прогонки
    n = n-1
    alpha = np.zeros(n)
    beta = np.zeros(n)

    y = np.zeros(n)
    y[0] = b[0]
    alpha[0] = -c[0] / y[0]
    beta[0] = d[0] / y[0]
    for i in range(1, n-1):
        y[i] = b[i] + a[i]*alpha[i-1]
        alpha[i] = -c[i] / y[i]
        beta[i] = (d[i] - a[i]*beta[i-1]) / y[i]
    y[n-1] = b[n-1] + a[n-1]*alpha[n-2]
    beta[n-1] = (d[n-1] - a[n-1]*beta[n-2]) / y[n-1]
    # обратный ход метода прогонки
    x = np.zeros(n)
    x[n-1] = beta[n-1]
    for i in range(n-2, -1, -1):
        x[i] = alpha[i]*x[i+1] + beta[i]

    # нахождение y0 и yn из граничных условий
    x = np.insert(x, 0, A_)
    x = list(x)
    x.append(B_)
    return x


def punkt4a(f, h, n, X, a, b, A_, B_, k1, k2, x0, C):
    medium = 0.5*(b + a)
    #заглушки, т.к. только 2 материала
    medium2 = b + h 
    k3 = list(np.zeros(len(k1)))
    u, label = [], []
    for i in range(len(k1)):
        u.append(findSolution([k1[i], k2[i], k3[i]], f, h, n, X, A_, B_, a, b, medium, medium2, x0, C))
        label.append('k1={:}, k2={:}'.format(k1[i], k2[i]))
    #print("\nВектор-решение задачи:")
    #print_array(u)
    plot_res(len(u), X, u, label, 'Мощн. ист. С={:}, коорд. x0={:}, k1{:}k2'.format(
        C, x0, '>>' if k1>k2 else '<<'))
    #plot_res_pro(len(u), X, u, label, 'Мощн. ист. С={:}, коорд. x0={:}, k1{:}k2'.format(
    #C, x0, '>>' if k1>k2 else '<<'))


def punkt4b(f, h, n, X, a, b, A_, B_, k1, k2, k3, x0, C):
    c1 = a + (b - a)/3
    c2 = a + 2*(b - a)/3
    u, label = [], []
    for i in range(len(k1)):
        u.append(findSolution([k1[i], k2[i], k3[i]], f, h, n, X, A_, B_, a, b, c1, c2, x0, C))
        label.append('k1={:}, k2={:}, k3={:}'.format(k1[i], k2[i], k3[i]))
    if k1>k2>k3: text = 'k1>k2>k3'
    elif k1<k2<k3: text = 'k1<k2<k3'
    elif k1==k3<k2: text = 'k1=k3=k k2=2k'
    elif k1==k3>k2: text = 'k1=k2=20k k2=k'
    plot_res(len(u), X, u, label, 'Мощн. ист. С={:}, коорд. x0={:}, {:}'.format(C, x0, text))
    #plot_res_pro(len(u), X, u, label, 'Мощн. ист. С={:}, коорд. x0={:}, {:}'.format(C, x0, text))


def task2():

    test = True

    # условие -d/dx(k(x)*du/dx) = f   

    if not test:
        # Вариант 3
        a = 0.5
        b = 1.5
        A_ = 2
        B_ = 6
    else:
        # Тестовый пример (Вариант 1)
        a = 1
        b = 2
        A_ = 3
        B_ = 0

    def f(x, x0, C):
            if abs(x - x0) - h/2 < 1e-5:
                return C/2
            elif x - h/2 < x0 < x + h/2:
                return C
            else:
                return 0

    print("Задание 2.\nПромоделировать стационарные процессы теплопроводности стержня в зависимости" +
          " от входных данных задачи – переменного коэффициента теплопроводности k(x) и плотности" + 
          " источников тепла f(x)")

    h = (b - a) / 150

    print("\nМетодом баланса (с использованием метода прогонки)")
  
    n = int((b - a) / h)
    X = np.zeros(n+1)
    for i in range(n+1):
        X[i] = a + i * h
    
    # пункт 4a
    if not test:
        k1 = [[0.7, 0.4, 0.1], 
              [50, 10, 2]]
        k2 = [[50, 10, 2],
              [0.7, 0.4, 0.1]]
    else:
        k1, k2 = [[0.1, 0.4], [2, 10]], [[2, 10], [0.1, 0.4]]

    # пункт 5а
    # источник тепла x0 в центре отрезка C - его мощность
    x0 = [(b + a)/2]
    if not test:
        C = [[10], [50], [200]]
    else:
        C = [[50]]
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4a(f, h, n, X, a, b, A_, B_, k1[i], k2[i], x0, C[j])
    # пункт 5б
    # 2 источникa тепла x0 (симметроично центра), C - мощности (одинаковые)
    x0 = [(b + a)/2-0.3, (b + a)/2+0.3]
    if not test:
        C = [[10, 10], [50, 50], [200, 200]]
    else:
        C = [[50, 50]]
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4a(f, h, n, X, a, b, A_, B_, k1[i], k2[i], x0, C[j])
    # пункт 5в
    # 2 источникa тепла x0(симметроично центра), C - мощности (разные)
    x0 = [(b + a)/2-0.3, (b + a)/2+0.3]
    if not test:
        C = [[50, 200], [200, 50]]
    else:
        C = [[50, 200]]
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4a(f, h, n, X, a, b, A_, B_, k1[i], k2[i], x0, C[j])
    # пункт 5г
    # 2 источникa тепла x0(свое расположение (1.3)), C - мощности (разные)
    x0 = [a + (b-a)/8, (b + a)/2 + (b-a)/8]
    if not test:
        C = [[50, 200], [200, 50], [50, 50], [200, 200]]
    else:
        C = [[50, 50], [50, 200]]
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4a(f, h, n, X, a, b, A_, B_, k1[i], k2[i], x0, C[j])
    
    # пункт 4б
    if not test:
        k1 = [[10, 0.75, 58, 0.6],
              [12, 2.6, 103, 0.9],
              [0.6, 3, 32, 0.9],
              [12, 58, 34, 18]]
        k2 = [[11, 1.2, 85, 0.7],
              [11, 1.2, 85, 0.7],
              [1.2, 6, 64, 1.8],
              [0.6, 2.9, 1.7, 0.9]]
        k3 = [[12, 2.6, 103, 0.9],
              [10, 0.75, 58, 0.6],
              [0.6, 3, 32, 0.9],
              [12, 58, 34, 18]]
    else:
        k1 = [[10, 0.75],
              [12, 2.6],
              [0.6, 3],
              [12, 58]]
        k2 = [[11, 1.2],
              [11, 1.2],
              [1.2, 6],
              [0.6, 2.9]]
        k3 = [[12, 2.6],
              [10, 0.75],
              [0.6, 3],
              [12, 58]]

    # пункт 5а
    # источник тепла x0 в центре отрезка C - его мощность
    x0 = [(b + a)/2]
    if not test:
        C = [[10], [50], [200]]
    else:
        C = [[50]]
    for i in range(len(k1)):
        for j in range(len(C)):
             punkt4b(f, h, n, X, a, b, A_, B_, k1[i], k2[i], k3[i], x0, C[j])

    # пункт 5б
    # 2 источникa тепла x0 (симметроично центра), C - мощности (одинаковые)
    x0 = [(b + a)/2-0.3, (b + a)/2+0.3]
    if not test:
        C = [[10, 10], [50, 50], [200, 200]]
    else:
        C = [[50, 50]] 
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4b(f, h, n, X, a, b, A_, B_, k1[i], k2[i], k3[i], x0, C[j])

    # пункт 5в
    # 2 источникa тепла x0(симметроично центра), C - мощности (разные)
    x0 = [(b + a)/2-0.3, (b + a)/2+0.3]
    if not test:
        C = [[50, 200], [200, 50]]
    else:
        C = [[50, 200]]
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4b(f, h, n, X, a, b, A_, B_, k1[i], k2[i], k3[i], x0, C[j])
    
    # пункт 5г
    # 2 источникa тепла x0(свое расположение (1.3)), C - мощности (разные)
    x0 = [a + (b-a)/8, (b + a)/2 + (b-a)/8]
    if not test:
        C = [[50, 200], [200, 50], [50, 50], [200, 200]]
    else:
        C = [[50, 200], [50, 50]]
    for i in range(len(k1)):
        for j in range(len(C)):
            punkt4b(f, h, n, X, a, b, A_, B_, k1[i], k2[i], k3[i], x0, C[j])
    
    

        