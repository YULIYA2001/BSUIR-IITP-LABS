import numpy as np
import matplotlib.pyplot as plt
import math
from random import uniform as random
from scipy import stats



################################################################################################################
################################################# Lab 1 ########################################################
################################################################################################################

# Y = fi(X) = x^(1/3)  -  X равномерно распределено на [-1, 1]
def fi(x):
    if x > 0:
        return x ** (1/3)
    return -(-x)**(1/3)


Ax, Bx = -1, 1
Ay, By = -1, 1


def f(y):
    if Ay < y < By: 
        return 3 / 2 * y**2
    return 0


def F(y):
    if y < Ay: 
        return 0
    if Ay <= y < By: 
        return 1/2 + y**3 / 2
    if By <= y: 
        return 1


def sample(n):
    Y = []
    for i in range(n):
        x = random(0, 1) * (Bx - Ax) + Ax
        Y.append(fi(x))
    return Y


def variation_range(Y):
    Y.sort()
    return Y


def empirical_function(Y):
    N = len(Y)
    res = {}
    for i in range(N):
        if not Y[i] in res:
            res[Y[i]] = i + 1
        else:
            res[Y[i]] += 1

    x, n = [], []
    for value, count in res.items():
        x.append(value)
        n.append(count / N)

    return x, n  


def lab1():

    print('-'*50, 'Lab 1', '-'*50)

    # n - объем выборки
    n = 10

    Y = sample(n)
    print("Выборка: ")
    for i in range(len(Y)):
        print("%.4f" % Y[i], end='  ')
    print()

    Y = variation_range(Y)
    print("Вариационный ряд: ")
    for i in range(len(Y)):
        print("%.4f" % Y[i], end='  ')
    print()

    y, Fy = empirical_function(Y)

    print("Эмпирическая функция: ")
    print("  y         F(y)")
    for i in range(len(y)):
        print("%.4f" % y[i] if y[i] < 0 else " %.4f" % y[i], "   %.4f" % Fy[i])

    x_pl, y_pl = y.copy(), Fy.copy() 
    x_pl.insert(0, Ay-0.1)
    y_pl.insert(0, 0)
    x_pl.append(By+0.1)
    y_pl.append(1)
    fig, ax = plt.subplots()
    ax.step(x_pl, y_pl, "r-", where='post', label = "Эмпирическая функция")
    # выколотые точки графика
    y_pl.pop(0)
    x_pl.pop(0)
    y_pl.pop()
    x_pl.pop()
    ax.scatter(x_pl, y_pl, s=25, c="w", marker="o", edgecolors="k")
    # сетка
    ax.grid()

    x_pl_t = np.linspace(Ay-0.1, By+0.1, 1000)
    y_pl_t = [F(x) for x in x_pl_t]
    ax.plot(x_pl_t, y_pl_t, label = "Аналитическая функция")
    ax.legend()
    plt.show()

    print('\n\n', '-'*106, '\n\n')





################################################################################################################
################################################# Lab 2 ########################################################
################################################################################################################

def coef_ABFv_eq_interval(Y, M):
    n = len(Y)
    h = (Y[-1] - Y[0]) / M
    
    A, B = [Y[0]], []
    for i in range(1,M):
        A.append(Y[0] + i*h)
        B.append(A[-1])
    B.append(Y[-1])

    v = np.zeros(M)
    i, j = 0, 0
    while i < n:
        while Y[i] < B[j]:
            v[j] += 1
            i += 1
        if Y[i] == B[j]:
            if j == len(B)-1:
                v[j] += 1
                i +=1
            else:
                v[j] += 0.5
                v[j+1] += 0.5
                i += 1
        j += 1

    F = []
    for i in range(M):
        F.append(v[i] / (n*h))

    return A, B, F, v, h


def coef_ABFv_equiprobable(Y, M):

    n = len(Y)
    v = int(n / M)

    A, B = [Y[0]], []
    for i in range(1, M):
        A.append((Y[i*v-1] + Y[i*v]) / 2)
        B.append(A[i])
    B.append(Y[-1])

    h = []
    a = A.copy()
    a.append(B[-1])
    for i in range(M):
        h.append(a[i+1] - a[i])

    F = []
    for i in range(M-1):
        F.append(v / (n*h[i]))
    # "лишние" точки в последний интервал
    F.append((n - v*(M - 1)) /  (n*h[-1]))

    V = [v]*M
    V[M-1] = n - v*(M - 1)

    return A, B, F, V, h


def plot_all_charts(A, B, F, v, n):
    # гистограмма
    x_pl, y_pl = A.copy(), F.copy()
    x_pl.insert(0, A[0])
    y_pl.insert(0, 0)
    x_pl.append(B[-1])
    y_pl.append(0)
    fig, ax = plt.subplots()
    ax.step(x_pl, y_pl, "r-", where='post', label = "Гистограмма")

    # полигон распределения
    dots = B.copy()
    dots.insert(0, A[0])
    x_pl_p = [dots[0]]
    for i in range(len(dots)-1):
        x_pl_p.append((dots[i+1] + dots[i]) / 2)
    x_pl_p.pop(0)
    freq = []
    for i in range(len(v)):
        freq.append(v[i]/n)
    y_pl_p = freq
    ax.plot(x_pl_p, y_pl_p, 'g-o', label="Полигон распределения")

    # теоритическая функция плотности распределения
    x = np.linspace(Ay, By, 1000)
    y = [f(i) for i in x]
    ax.plot(x, y, color='k', label="Аналитическая функция")
    
    ax.legend()
    ax.grid()
    plt.show()


def plot(A, B, v, n):
    dots = B.copy()
    dots.insert(0, A[0])
    dots.append(By)
    dots.insert(0, Ay-0.2)
    dots.append(By+0.2)
    freq, y = [v[0]/n], [v[0]/n]
    for i in range(1, len(v)):
        freq.append(v[i]/n)
        y.append(y[-1] + freq[i])
    y.insert(0, 0)
    y.insert(0, 0)
    y.append(1)
    y.append(1)
    x = dots
    fig, ax = plt.subplots()
    ax.plot(x, y, label="Функция распределения по сгр. данным")

    x_pl_t = np.linspace(Ay-0.1, By+0.1, 1000)
    y_pl_t = [F(x) for x in x_pl_t]
    ax.plot(x_pl_t, y_pl_t, label = "Аналитическая функция")
    ax.legend()
    ax.grid()
    plt.show()


def print_table(A, B, v, h, F):

    dots = B.copy()
    dots.insert(0, A[0])
    y = []
    for i in range(len(dots)-1):
        y.append((dots[i+1] + dots[i]) / 2)

    n = len(A)
    print("   i   |    Ai    |    Bi    |    vi   |   hi    |   fi*   |    y")
    print("---------------------------------------------------------------------")
    for i in range(n):
        print("%5d" % (i+1), 
              " | %.4f" % A[i] if A[i] < 0 else " |  %.4f" % A[i],
              " | %.4f" % B[i] if B[i] < 0 else " |  %.4f" % B[i],
              " | %6d" % v[i],
              " | %.4f" % h[i],
              " | %.4f" % F[i],
              " | %.4f" % y[i] if y[i] < 0 else " |  %.4f" % y[i]
              )


def lab2():

    print('-'*50, 'Lab 2', '-'*50)

    # n - объем выборки
    n = 100
    # M - количество интервалов
    if n <= 100:
        M = (int)(n**0.5) 
    else:
        M = (int)(math.log10(n)*2)
        for m in [(int)(math.log10(n)*3), (int)(math.log10(n)*4)]:
            if n % m == 0:
                M = m
    # M = 10

    Y = variation_range(sample(n))

    print("Вариационный ряд: ")
    i = 0
    while i < len(Y):
        for j in range(M):
            print("%.4f" % Y[i] if Y[i] < 0 else " %.4f" % Y[i], end='  ')
            i += 1
            if i >= len(Y):
                break
        print()
    print()


    #--------------------------------------- Задание 2 (равноинтервальный метод) -------------------------------
    A, B, F, v, h = coef_ABFv_eq_interval(Y, M)
    print("Равноинтервальный метод")
    print_table(A, B, v, [h]*M, F)
    plot_all_charts(A, B, F, v, n)
    plot(A, B, v, n)
    
    # Проверка суммы площади столбиков гистограммы
    sum = 0
    A.append(B[-1])
    for i in range(len(A)-1):
        sum += F[i]*(A[i+1]-A[i])
    print("S = ", sum)
    print()


    #----------------------------------- Задание 3 (равновероятностный метод) ------------------------------
    A, B, F, v, h = coef_ABFv_equiprobable(Y, M)
   
    print("Равновероятостный метод")
    print_table(A, B, v, h, F)
    plot_all_charts(A, B, F, v, n)
    plot(A, B, v, n)

    # Проверка суммы площади столбиков гистограммы
    sum = 0
    A.append(B[-1])
    for i in range(len(A)-1):
        sum += F[i]*(A[i+1]-A[i])
    print("S = ", sum)

    print('\n\n', '-'*106, '\n\n')







################################################################################################################
################################################# Lab 3 ########################################################
################################################################################################################

#--------------------------------------------- Критерий Пирсона ------------------------------------------------

def plot_hist(A, B, F, Y):
    """Построение гистограммы и аналитической функции для функции плотности"""

    x_pl, y_pl = A.copy(), F.copy()
    x_pl.insert(0, A[0])
    y_pl.insert(0, 0)
    x_pl.append(B[-1])
    y_pl.append(0)
    fig, ax = plt.subplots()
    ax.step(x_pl, y_pl, "r-", where='post', label = "Гистограмма равновер. методом")
    ax.scatter(Y, [0]*len(Y), s=1, c="k", marker="o", edgecolors="k")

    x = np.linspace(Ay, By, 1000)
    y = [f(i) for i in x]
    ax.plot(x, y, color='k', label="Аналитическая функция")
    ax.legend()
    ax.grid()
    plt.show()


def print_variation_range(Y):
    """Вывод вариационного ряда на экран"""

    n =  len(Y)
    print("Вариационный ряд (", n, " СВ): ")
    i = 0
    while i < n:
        for j in range(10):
            print("%.4f" % Y[i] if Y[i] < 0 else " %.4f" % Y[i], end='  ')
            i += 1
            if i >= n:
                break
        print()
    print()


def X_square(A, B, M, n, v):
    """Расчет значения критерия хи-квадрат"""

    Ax = A.copy()
    Ax.append(B[-1])
    X_sq, sum_pi = 0, 0
    for i in range(M):
        p = F(Ax[i+1]) - F(Ax[i])
        p_ = v[i] / n
        X_sq += n * (p - p_)**2 / p
        sum_pi += p

    good = False
    if abs(1-sum_pi) <= 0.01:
        print("\nКонтрольное соотношение для суммы Pi выполняется")
        print(abs(1-sum_pi), "<= 0.01\n")
        good = True
        
    return X_sq, good


def Pirson_criterion():
    """Проверка гипотезы по критерию согласия Пирсона"""

    n = 200
    print("\t\t\t Критерий X^2 Пирсона")
    M = (int)(math.log10(n)*3)
    print("M =", M, "разрядов")

    # менять выборку, если не выполняется контрольное соотношенеие E(Pi)~1
    while True:
        Y = variation_range(sample(n))
        A, B, F, v, h = coef_ABFv_equiprobable(Y, M)
        X_sq, good = X_square(A, B, M, n, v)
        if good:
            break

    # print()
    # print_variation_range(Y)
    # print_table(A, B, v, h, F)
    plot_hist(A, B, F, Y)
    # k = 5 значения Х для а из таблицы: a = 0.1 - X = 9.236, a = 0.05 - X = 11.070, a = 0.01 - X = 15.086
    X_tb = [9.236, 11.070, 15.086]
    a = [0.1, 0.05, 0.01]
    for i in range(3):
        print('a = ', a[i], '\n',
              'X^2 = {:.4f}'.format(X_sq), 
              '>' if X_sq > X_tb[i] else '<',
              X_tb[i],
              ' => гипотеза отклоняется' if X_sq > X_tb[i] else ' => гипотеза принимается')





#------------------------------------------- Критерий Колмогорова ----------------------------------------------

def plot_empirical_and_analytical_function(y, Fy):
    x_pl, y_pl = y.copy(), Fy.copy() 
    x_pl.insert(0, Ay-0.1)
    y_pl.insert(0, 0)
    x_pl.append(By+0.1)
    y_pl.append(1)
    fig, ax = plt.subplots()
    ax.step(x_pl, y_pl, "r-", where='post', label = "Эмпирическая функция")
    # выколотые точки графика
    y_pl.pop(0)
    x_pl.pop(0)
    y_pl.pop()
    x_pl.pop()
    ax.scatter(x_pl, y_pl, s=25, c="w", marker="o", edgecolors="r")    

    x_pl_t = np.linspace(Ay, By, 20)
    y_pl_t = [F(x) for x in x_pl_t]
    ax.plot(x_pl_t, y_pl_t, 'b', label = "Аналитическая функция")
    ax.scatter(x_pl_t, y_pl_t, s=10, c="b", marker="o", edgecolors="b")
    ax.grid()
    ax.legend()
    plt.show()


def max_deviation(y, Fy):

    max_d_pl = -1000
    for i in range(len(y)):
        d_pl = abs(Fy[i] - F(y[i]))
        if d_pl > max_d_pl:
            max_d_pl = d_pl
            point_pl = (y[i], Fy[i])
       
    Fy2 = Fy.copy()
    Fy2.pop()
    Fy2.insert(0,0)
    max_d_mi = -1000
    for i in range(len(y)):
        d_mi = abs(Fy2[i] - F(y[i]))
        if d_mi > max_d_mi:
            max_d_mi = d_mi
            point_mi = (y[i], Fy2[i])

    if max_d_pl > max_d_mi:
        return max_d_pl, point_pl

    return max_d_mi, point_mi


def Kolmogorov_criterion():
    """Проверка гипотезы по критерию согласия Колмогорова"""

    n = 30
    print("\n\n\t\t\t Критерий Колмогорова")

    # построение вариационного ряда
    Y = variation_range(sample(n))
    # print_variation_range(Y)
    
    # построение графика эмпирической функции распределения
    y, Fy = empirical_function(Y)
    # print("Эмпирическая функция:\n  y         F(y)")
    # for i in range(len(y)):
    #     print("%.4f" % y[i] if y[i] < 0 else " %.4f" % y[i], "   %.4f" % Fy[i])
    # plot_empirical_and_analytical_function(y, Fy)

    # определение мах отклонения эмпирической функции от теоретической
    max_d, point = max_deviation(y, Fy)
    print("Максимальное отклонение {:.4f} в точке ({:.4f}, {:.4f})".format(max_d, point[0], point[1]))
    plot_empirical_and_analytical_function(y, Fy)

    # вычисление значения критерия (Лямбда)
    criterion = n**(1/2) * max_d

    L_tb = [1.22, 1.36, 1.63]
    a = [0.1, 0.05, 0.01]
    for i in range(3):
        print('a = ', a[i], '\n',
              'Lambda = {:.4f}'.format(criterion),
              '>' if criterion > L_tb[i] else '<',
              L_tb[i],
              ' => гипотеза отклоняется' if criterion > L_tb[i] else ' => гипотеза принимается')


#------------------------------------------- Критерий Мизеса ----------------------------------------------

def Mises_criterion():
    """Проверка гипотезы по критерию согласия Мизеса"""

    n = 50
    print("\n\n\t\t\t Критерий Мизеса")

    Y = variation_range(sample(n))
    # print_variation_range(Y)

    y, Fy = empirical_function(Y)
    F_teor = [F(x) for x in y]

    sum = 0
    for i in range(n):
        sum += (F(y[i]) - (i - 0.5)/n)**2
    criterion = 1/(12 * n) + sum

    L_tb = [0.347, 0.461, 0.744]
    a = [0.1, 0.05, 0.01]
    for i in range(3):
        print('a = ', a[i], '\n',
              'Lambda = {:.4f}'.format(criterion),
              '>' if criterion > L_tb[i] else '<',
              L_tb[i],
              ' => гипотеза отклоняется' if criterion > L_tb[i] else ' => гипотеза принимается')


def lab3():

    print('-'*50, 'Lab 3', '-'*50)

    Pirson_criterion()
    Kolmogorov_criterion()
    Mises_criterion()
    
    print('\n\n', '-'*106, '\n\n')







################################################################################################################
################################################# Lab 4 ########################################################
################################################################################################################

#-------------------------------------- 1. Доверительный интервал для МО ---------------------------------------

def M_t(): 
    return 0

def D_t(): 
    return 3/5


def T(alpha, k):
    return stats.t.ppf(alpha, k)


def plot_alpha_interval_size(level, inter_size, str, type='M'):
    '''График зависимости величины доверит. интервала от уровня значимости'''
    fig, ax = plt.subplots()
    ax.grid()
    ax.plot(level, inter_size, 'r-o')
    if type == 'M':
        plt.title("D "+ str + "известна")
    elif type == 'D':
        plt.title("M "+ str + "известнo")
    plt.xlabel('уровень значимости')
    plt.ylabel('величина доверительного интервала')
    #ax.legend()
    plt.show()


def comparison_plot_alpha_interval_size(level, inter_size1, inter_size2, str1, str2, n, type='M'):
    '''2 графика зависимости величины доверит. интервала от уровня значимости для сравнения'''
    fig, ax = plt.subplots()
    ax.grid()
    plt.title('n = {:}'.format(n))
    plt.xlabel('уровень значимости')
    plt.ylabel('величина доверительного интервала')
    if type == 'M':
        ax.plot(level, inter_size1, 'r-o', label = "D "+ str1 + "известна")
        ax.plot(level, inter_size2, 'b-o', label = "D "+ str2 + "известна")
    elif type == 'D':
        ax.plot(level, inter_size1, 'r-o', label = "M "+ str1 + "известнo")
        ax.plot(level, inter_size2, 'b-o', label = "M "+ str2 + "известнo")
    ax.legend()
    plt.show()


def table_for_confidence_interval_M(level, m_dots, eps):
    '''Таблица зависимости доверительного интервала MO от уровня значимости'''
    print("Уровень значимости   Доверительный интервал МО   Накрывает MO?")
    for i in range(3):
        print("%10.2f" % level[i], 
              "           [{:.4f}, {:.4f}]".format(m_dots-eps[i], m_dots+eps[i]),
              "          ", ('Да' if m_dots-eps[i] < m_dots < m_dots+eps[i] else 'Нет'))


def repeat_for_diff_n_M(n):
    '''Повторить пункты 1.2 - 1.8 для различных n'''
    print("-"*100, "\nn = ", n)
    Y = variation_range(sample(n))
    m_dots = sum(Y) / n
    print("Точечная оценка МО СВ: ", m_dots)
    print('Теоретическое значение МО СВ по известной плотности распределения: ', M_t())

    D_dots = 0
    for x in Y:
        D_dots += (x - m_dots) ** 2 
    D_dots /= (n - 1)
    print("\nТочечная оценка дисперсии СВ: ", D_dots)
    print('Теоретическое значение дисперсии СВ по известной плотности распределения: ', D_t())

    level = [0.1, 0.05, 0.01]
    level_value_normal = [1.64, 1.96, 2.58]
    # Student => t(1 - alpha/2, k)
    level_value_Student = [T((0.95), n-1), T((0.975), n-1), T((0.995), n-1)]

    if n > 30:
        eps = [(u * (D_dots / n)**0.5) for u in level_value_normal]
    else:
        eps = [(t * (D_dots / n)**0.5) for t in level_value_Student]
    print('\nДоверительный интервал для оценки МО={:.4f} СВ при неизвестной D={:.4f} для различных '\
       'уровней значимости.'.format(m_dots, D_dots))
    table_for_confidence_interval_M(level, m_dots, eps)

    eps_D = [(u * (D_t() / n)**0.5) for u in level_value_normal]
    print('\nДоверительный интервал для оценки МО={:.4f} СВ при известной D={:} для различных уровней '\
         'значимости.'.format(m_dots, D_t()))
    table_for_confidence_interval_M(level, m_dots, eps_D)   
    
    interval = [(2 * eps[i]) for i in range(3)]
    interval_D = [(2 * eps_D[i]) for i in range(3)]
    comparison_plot_alpha_interval_size(level, interval, interval_D, "не", "", n, type='M')

    return interval, interval_D


def plot_inter_size_V(V, level, inter, inter_D, type='M'):
    '''Графики зависимости величины доверит. интервала от V выборки'''
    fig, ax = plt.subplots()
    ax.grid()
    if type == 'M':
        plt.title('!D - неизвестна, D - известна')
    elif type == 'D':
        plt.title('!M - неизвестнo, M - известнo')
    plt.xlabel('n - объем выборки')
    plt.ylabel('величина доверительного интервала')
    color = ['r', 'b', 'g']
    for i in range(3):
        if type == 'M':
            ax.plot(V, [inter[n][i] for n in range(len(V))],
                   color[i]+'-o', label = "!D alpha = {:}".format(level[i]))
            ax.plot(V, [inter_D[n][i] for n in range(len(V))],
                   color[i]+':o', label = "D alpha = {:}".format(level[i]))
        elif type == 'D':
            ax.plot(V, [inter[n][i] for n in range(len(V))],
                   color[i]+'-o', label = "!M alpha = {:}".format(level[i]))
            ax.plot(V, [inter_D[n][i] for n in range(len(V))],
                   color[i]+':o', label = "M alpha = {:}".format(level[i]))
    ax.legend()
    plt.show()


def full_estimate_of_M(n):
    '''Полная оценка МО'''

    # Пункт 1.1
    print('1.1.\n---------')
    Y = variation_range(sample(n))
    print_variation_range(Y)
    m_dots = sum(Y) / n
    print("Точечная оценка МО СВ: ", m_dots)
    print("Теоретическое МО СВ:   ", M_t())

    # Пункт 1.2
    print('\n1.2.\n---------')
    D_dots = 0
    for x in Y:
        D_dots += (x - m_dots) ** 2 
    D_dots /= (n - 1)
    print("Точечная оценка дисперсии СВ: ", D_dots)

    # Пункт 1.3
    print('\n1.3.\n---------')
    # значения альфа - уровень значимости
    level = [0.1, 0.05, 0.01]
    # квантили по таблице Стьюдента для степеней свободы n - 1 = 19 для alpha [0.1, 0.05, 0.01]
    # Student => t(1 - alpha/2, k)
    level_value_Student = [T((0.95), n-1), T((0.975), n-1), T((0.995), n-1)]

    eps = [(t * (D_dots / n)**0.5) for t in level_value_Student]

    print('Доверительный интервал для оценки МО={:.4f} СВ при неизвестной D={:.4f} для различных '\
       'уровней значимости:\n'.format(m_dots, D_dots))
    table_for_confidence_interval_M(level, m_dots, eps)
    
    # Пункт 1.4
    print('\n1.4.\n---------\nГрафик зависимости величины доверит. интервала от уровня значимости (D неизвестна)')
    interval = [(2 * eps[i]) for i in range(3)]
    plot_alpha_interval_size(level, interval, "не", type='M')

    # Пункт 1.5
    print('\n1.5.\n---------')
    print('Теоретическое значение дисперсии СВ по известной плотности распределения: ', D_t())

    # Пункт 1.6
    print('\n1.6.\n---------')
    # квантили для стандартного нормального распределения для level = [0.1, 0.05, 0.01] 
    level_value_normal = [1.64, 1.96, 2.58]

    eps_D = [(u * (D_t() / n)**0.5) for u in level_value_normal]

    print('Доверительный интервал для оценки МО={:.4f} СВ при известной D={:} для различных уровней '\
         'значимости:\n'.format(m_dots, D_t()))
    table_for_confidence_interval_M(level, m_dots, eps_D)

    # Пункт 1.7
    print('\n1.7.\n---------\nГрафик зависимости величины доверит. интервала от уровня значимости (D известна)')
    interval_D = [(2 * eps_D[i]) for i in range(3)]
    plot_alpha_interval_size(level, interval_D, "", type='M')

    # Пункт 1.8
    print('\n1.8.\n---------\nСравнение графиков п.п. 1.4 и 1.7')
    comparison_plot_alpha_interval_size(level, interval, interval_D, "не", "", n, type='M')

    # Пункт 1.9
    print('\n1.9.\n---------\nПункты 1.2 - 1.8 для n = 30, 50, 70, 100, 150')

    V = [30, 50, 70, 100, 150]
    # массивы [[a1, a2, a3], ...] хранят размер интервалов для 3 разных уровней значимости для разных n
    inter, inter_D = [], []
    for n in V:
        temp = repeat_for_diff_n_M(n)
        inter.append(temp[0])
        inter_D.append(temp[1])


    # Пункт 1.10
    print('\n1.10.\n---------\nГрафики зависимости величины доверит. интервала от V выборки')
    
    V.insert(0, 20)
    inter.insert(0, interval)
    inter_D.insert(0, interval_D)

    plot_inter_size_V(V, level, inter, inter_D, type='M')






#----------------------------------- 2. Доверительный интервал для дисперсии ----------------------------------

def X2(alpha, k):
    return stats.chi2.ppf(alpha, k)


def table_for_confidence_interval_D(level, D_dots, l_border, r_border):
    '''Таблица зависимости доверительного интервала для дисперсии от уровня значимости'''
    print("Уровень значимости   Доверительный интервал D   Накрывает D?")
    for i in range(3): 
        print("%10.2f" % level[i], 
              "           [{:.4f}, {:.4f}]".format(l_border[i], r_border[i]),
              "          ", ('Да' if l_border[i] < D_dots < r_border[i] else 'Нет'))


def repeat_for_diff_n_D(n):
    '''Повторить пункты 2.2 - 2.8 для различных n'''
    print("-"*100, "\nn = ", n)
    Y = variation_range(sample(n))
    m_dots = sum(Y) / n
    D_dots = 0
    for x in Y:
        D_dots += (x - m_dots) ** 2 
    D_dots /= (n - 1)
    print("Точечная оценка дисперсии СВ: ", D_dots)
    print('Теоретическое значение дисперсии СВ по известной плотности распределения: ', D_t())

    print("\nТочечная оценка МО СВ: ", m_dots)
    print('Теоретическое значение MO СВ по известной плотности распределения: ', M_t())

    level = [0.1, 0.05, 0.01]
    X2_for_alpha_div_2 = [X2(0.95, n-1), X2(0.975, n-1), X2(0.995, n-1)] 
    X2_for_1_minus_alpha_div_2 = [X2(0.05, n-1), X2(0.025, n-1), X2(0.005, n-1)] 
    l_border = [( (n-1) * D_dots / X2_for_alpha_div_2[i] ) for i in range(3)]
    r_border = [( (n-1) * D_dots / X2_for_1_minus_alpha_div_2[i] ) for i in range(3)]
    print('\nДоверительный интервал для оценки D={:.4f} СВ при неизвестном M={:.4f} для различных '\
       'уровней значимости.'.format(D_dots, m_dots))
    table_for_confidence_interval_D(level, D_dots, l_border, r_border)

    S1_sq = 0
    for x in Y:
        S1_sq += (x - M_t()) ** 2 
    S1_sq /= n

    X2_for_alpha_div_2_M = [X2(0.95, n), X2(0.975, n), X2(0.995, n)] 
    X2_for_1_minus_alpha_div_2_M = [X2(0.05, n), X2(0.025, n), X2(0.005, n)]
    l_border_M = [( n * S1_sq / X2_for_alpha_div_2_M[i] ) for i in range(3)]
    r_border_M = [( n * S1_sq / X2_for_1_minus_alpha_div_2_M[i] ) for i in range(3)]
    print('\nДоверительный интервал для оценки D={:.4f} СВ при известном M={:} для различных уровней '\
         'значимости.'.format(D_dots, M_t()))
    table_for_confidence_interval_D(level, D_dots, l_border_M, r_border_M) 

    interval = [(r_border[i] - l_border[i]) for i in range(3)]
    interval_M = [(r_border_M[i] - l_border_M[i]) for i in range(3)]
    comparison_plot_alpha_interval_size(level, interval, interval_M, "не", "", n, type='D')

    return interval, interval_M



def full_estimate_of_D(n):
    '''Полная оценка дисперсии'''

    # Пункт 2.1
    print('2.1.\n---------')
    Y = variation_range(sample(n))
    print_variation_range(Y)
    m_dots = sum(Y) / n
    D_dots = 0
    for x in Y:
        D_dots += (x - m_dots) ** 2 
    D_dots /= (n - 1)
    print("Точечная оценка дисперсии СВ: ", D_dots)

    # Пункт 1.2
    print('\n1.2.\n---------')
    print("Точечная оценка МО СВ: ", m_dots)

    # Пункт 2.3
    print('\n2.3.\n---------')
    level = [0.1, 0.05, 0.01]
    # квантили по таблице хи-квадрат для степеней свободы n-1 = 19 для alpha/2 и 1-alpha/2
    # где alpha => [0.1, 0.05, 0.01]
    X2_for_alpha_div_2 = [30.14353, 32.85233, 38.58226] 
    X2_for_1_minus_alpha_div_2 = [10.11701, 8.90652, 6.84397] 

    l_border = [( (n-1) * D_dots / X2_for_alpha_div_2[i] ) for i in range(3)]
    r_border = [( (n-1) * D_dots / X2_for_1_minus_alpha_div_2[i] ) for i in range(3)]

    print('Доверительный интервал для оценки D={:.4f} СВ при неизвестном M={:.4f} для различных '\
       'уровней значимости:\n'.format(D_dots, m_dots))
    table_for_confidence_interval_D(level, D_dots, l_border, r_border)

    # Пункт 2.4
    print('\n2.4.\n---------\nГрафик зависимости величины доверит. интервала от уровня значимости (M неизвестнo)')
    interval = [(r_border[i] - l_border[i]) for i in range(3)]
    plot_alpha_interval_size(level, interval, "не", type='D')

    # Пункт 2.5
    print('\n2.5.\n---------')
    print('Теоретическое значение МО СВ по известной плотности распределения: ', M_t())

    # Пункт 2.6
    print('\n2.6.\n---------')
    S1_sq = 0
    for x in Y:
        S1_sq += (x - M_t()) ** 2 
    S1_sq /= n

    X2_for_alpha_div_2_M = [31.41043, 34.16961, 39.99685] 
    X2_for_1_minus_alpha_div_2_M = [10.85081, 9.59078, 7.43384] 

    l_border_M = [( n * S1_sq / X2_for_alpha_div_2_M[i] ) for i in range(3)]
    r_border_M = [( n * S1_sq / X2_for_1_minus_alpha_div_2_M[i] ) for i in range(3)]

    print('Доверительный интервал для оценки D={:.4f} СВ при известном M={:} для различных уровней '\
         'значимости:\n'.format(D_dots, M_t()))
    table_for_confidence_interval_D(level, D_dots, l_border_M, r_border_M)

    # Пункт 2.7
    print('\n2.7.\n---------\nГрафик зависимости величины доверит. интервала от уровня значимости (M известнo)')
    interval_M = [(r_border_M[i] - l_border_M[i]) for i in range(3)]
    plot_alpha_interval_size(level, interval_M, "", type='D')

    # Пункт 2.8
    print('\n2.8.\n---------\nСравнение графиков п.п. 2.4 и 2.7')
    comparison_plot_alpha_interval_size(level, interval, interval_M, "не", "", n, type='D')

    # Пункт 2.9
    print('\n2.9.\n---------\nПункты 2.2 - 2.8 для n = 30, 50, 70, 100, 150')

    V = [30, 50, 70, 100, 150]
    # массивы [[a1, a2, a3], ...] хранят размер интервалов для 3 разных уровней значимости для разных n
    inter, inter_M = [], []

    for i in range(len(V)):
        temp = repeat_for_diff_n_D(V[i])
        inter.append(temp[0])
        inter_M.append(temp[1])

    # Пункт 2.10
    print('\n2.10.\n---------\nГрафики зависимости величины доверит. интервала от V выборки')
    
    V.insert(0, 20)
    inter.insert(0, interval)
    inter_M.insert(0, interval_M)

    plot_inter_size_V(V, level, inter, inter_M, type='D')



def lab4():
    print('-'*50, 'Lab 4', '-'*50)
    n = 20

    print("\n\n\t\t\t Доверительный интервал для МО")
    full_estimate_of_M(n)

    print("\n\n\t\t\t Доверительный интервал для дисперсии")
    full_estimate_of_D(n)
    



if __name__ == "__main__":
    #lab1()
    #lab2()
    #lab3()
    lab4()
    
