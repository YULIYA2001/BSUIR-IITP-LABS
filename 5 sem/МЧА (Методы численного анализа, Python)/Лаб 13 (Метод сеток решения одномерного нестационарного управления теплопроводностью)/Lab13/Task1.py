import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt
from scipy import linalg


def plot_res(n, X, y, label): 
    '''печать n графков по известным массивам и названиям'''
    fig = plt.figure()
    for i in range(n):
        plt.plot(X, y[i], label=label[i])
    plt.legend(loc='best')
    plt.show()


def findSolution(SET, f, K, C, A, B, a, b, needPrint):
    '''Аналитическое решение 
       SET - номер набора, f, K, C, A, B - функции из условия, a, b - границы по х,
       bool needPrint: 0 - ничего не печатать, 1 - печать основного, 2 - подробная печать'''
    x = sp.symbols('x')
    c1 = sp.symbols('c1')
    c2 = sp.symbols('c2')

    u = -sp.integrate( (  (sp.integrate(f(x), x) - c1) / K(x, SET)  ), x ) + c2
    if (needPrint == 2):
        print('Проинтегрируем исходное уравнение дважды (С = {:}):\nu(x) = {:}'.format(SET, u))
    elif (needPrint == 1):
        print('Набор параметров №{:}'.format(SET))

    u1 = u.subs(x, a)
    u2 = u.subs(x, b)
    if (needPrint == 2):
        print('Подставим граничные условия в полученное уравнение:')
        print('u({:}) = {:} = {:}'.format(a, u1, A(SET)))
        print('u({:}) = {:} = {:}'.format(b, u2, B(SET)))

    f1 = -float(u1.args[0]) + A(SET)
    c21 = float(u1.args[1].subs(c2,1))
    c11 = float(u1.args[2].subs(c1,1))

    f2 = -float(u2.args[0]) + B(SET)
    c22 = float(u2.args[1].subs(c2,1))
    c12 = float(u2.args[2].subs(c1,1))

    M = np.array([[c11, c21], [c12, c22]]) 
    v = np.array([f1, f2]) 
    #print(M)
    #print(v)
    c = list(linalg.solve(M, v))
    if (needPrint in [1, 2]):
        print('Решение системы линейных уравнений: \nс1 = {:},    c2 = {:}'.format(c[0], c[1]))

    u = u.subs(c1, c[0])
    u = u.subs(c2, c[1])
    if (needPrint in [1, 2]):
        print('Аналитическое решение:\n u(x) = ', u, '\n')
    return u


def task1():
    # условие -d/dx(K(x)*du/dx) = f   K(x) = K(x,C)

    # наборы данных (7 шт.)
    def C(set):
        if set in [1, 4, 5, 6, 7]:
            return 1
        if set == 2:
            return 2
        if set == 3:
            return 0.1

    def K(x, set):
        if set in [1, 2, 3, 5, 6, 7]:
            return C(set) * k(x)
        if set == 4:
            return 1 / k(x)

    def A(set):
        if set in [1, 2, 3, 4, 6]:
            return A_
        if set in [5, 7]:
            return -A_

    def B(set):
        if set in [1, 2, 3, 4, 5]:
            return B_
        if set in [6, 7]:
            return -B_

    # Вариант 3
    a = 0.5
    b = 1.5
    A_ = 2
    B_ = 6

    def k(x):
        return x**(-2)
 
    def f(x):
       return -2 * x**2 - 2*x  

    # Тестовый пример (Вариант 1)
    '''a = 1
    b = 2
    A_ = 3
    B_ = 0

    def k(x):
        return x**(3)
 
    def f(x):
       return 10 * x**(1/4)'''

   
    print("Задание 1.\nПромоделировать стационарные процессы теплопроводности стержня в зависимости" +
        " от входных данных задачи")
    # решение уравнения для всех наборов и значения у для графика для всех наборов
    u = []
    for i in range(7):
        u.append(findSolution(i+1, f, K, C, A, B, a, b, 0))
    X = np.linspace(a, b, 100)
    y = [[], [], [], [], [], [], []]
    for j in range(7):
        for i in range(len(X)):
            y[j].append(u[j].subs(sp.symbols('x'), X[i]))
    
    # Пункт 1, 2
    print('\n\n', '~'*10, 'Пункт 1-2', '~'*10)
    findSolution(1, f, K, C, A, B, a, b, 2)

    # Пункт 3
    print('\n\n', '~'*10, 'Пункт 3', '~'*10)
    for i in range(3):
        findSolution(i+1, f, K, C, A, B, a, b, 1)

    # Пункт 4
    print('\n\n', '~'*10, 'Пункт 4', '~'*10, '\nПостроение графиков')
    plot_res(3, X, [y[0], y[1], y[2]], ['Набор №1', 'Набор №2', 'Набор №3'])

    # Пункт 5
    print('\n\n', '~'*10, 'Пункт 5', '~'*10)
    findSolution(4, f, K, C, A, B, a, b, 2)
    plot_res(2, X, [y[0], y[3]], ['Набор №1', 'Набор №4'])

    # Пункт 6
    print('\n\n', '~'*10, 'Пункт 6', '~'*10)
    for i in range(5,8):
        findSolution(i, f, K, C, A, B, a, b, 1)
    plot_res(3, X, [y[4], y[5], y[6]], ['Набор №5', 'Набор №6', 'Набор №7'])

