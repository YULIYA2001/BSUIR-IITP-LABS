import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt

import CollocationMethod as CM
import IntegralLeastSquaresMethod as ILSM
import DiscreteLeastSquaresMethod as DLSM
import GalerkinMethod as GM
import Discrepancy as Dis

from Error import error


# k -  вариант
k = 3
a = np.sin(k)
b = np.cos(k)

# условие y" + p*y' + q*y = f
P = 0
x = sp.symbols('x')
Q = (1 + b*x**2)/a
F = -1/a
left = -1
right = 1

def fi(x, i):
    if i == 0:
        return 0
    if i > 0:
        return x**(i-1) * (1 - x**2)
    raise ValueError('Индекс функций базисной системы не может быть отрицательным. i>=0')


# Test1 y" + y = -x  точки коллокации X = [1/2, 1.4] - заменить в файле CollocationMethod.py
'''P = 0
Q = 1
F = -x
left = 0
right = 1

def fi(x, i):
    if i == 0:
        return 0
    if i > 0:
        return x**i * (1 - x)
    raise ValueError('Индекс функций базисной системы не может быть отрицательным. i>=0')'''

# Test2 y" + (1+x^2)y = -1
'''P = 0
Q = (1+x**2)
F = -1
left = -1
right = 1

def fi(x, i):
    if i == 0:
        return 0
    if i == 1:
        return 1-x**2
    if i == 2:
        return (x**2) * (1-x**2)'''


############################################
# n+1 - кол-во базисных функций
n = 5
# N - кол-во слагаемых в дискретном МНК
N = n*2


def y_granichn(x):
    if x == -1 or x == 1:
        return 0
    raise ValueError('Неверный аргумент. Это граничные условия. х=1 или х=-1.')


print("ЛР 11. Решение краевых задач. Методы коллокаций, наименьших квадратов и Галеркина\n")
print("\t\t\tВариант {:}".format(k))
print("-" * 50)
print("Методами коллокаций, Галеркина, интегральным и дискретным методами наименьших\n"+
     "квадратов получить численное решение краевой задачи")
print("Условие:")
print("sin({0}) * y\" + (1 + cos({0}) * x**2)*y = -1".format(k))

print("\nБазисная система:")
for i in range(n+1):
    print('fi[{:}] = {:}'.format(i, fi(x, i)))


############################################


def print_res(n, A, fi):
    print("\nПриближенное решение ДУ при n = {:}: \ny = ".format(n), end='')
    for i in range(len(A)):
        if A[i] == 0:
            continue
        elif A[i] > 0:
            print("+{:.5f}".format(A[i]), "*", fi(x, i+1), end=' ')
            continue
        print("{:.5f}".format(A[i]), "*", fi(x, i+1), end=' ')
    print()

# действие линейного оператора
def L(F, P, Q):
    diff2 = sp.diff(F, x, x)
    diff1 = sp.diff(F, x)
    res = diff2 + diff1 * P + F * Q
    return res

# подстановка полученного приближенного решения в уравнение
def my_F(A, fi, P, Q):
    x = sp.symbols('x')
    Y = 0
    for i in range(len(A)):
        Y += A[i] * fi(x, i+1)
    return L(Y, P, Q)

print("\n\nМетод коллокаций:\n" + '-'*70)
A1 = CM.collocation_method(P, Q, F, n, left, right, fi)
print_res(n, A1, fi)

print("\n\nИнтегральный МНК:\n" + '-'*70)
A2 = ILSM.integral_LSM(P, Q, F, n, left, right, fi)
print_res(n, A2, fi)

print("\n\nДискретный МНК:\n" + '-'*70)
print("N = ", N)
A3 = DLSM.discrete_LSM(P, Q, F, n, N, left, right, fi)
print_res(n, A3, fi)

print("\n\nМетод Галеркина:\n" + '-'*70)
A4 = GM.galerkin_method(P, Q, F, n, left, right, fi)
print_res(n, A4, fi)

print("\nСравнение методов\n", '-'*70)
print("Метод коллокаций A =", A1)
print("Интегральный МНК A =", A2)
print("Дискретный МНК A =", A3)
print("Метод Галеркина A =", A4)

A = [A1, A2, A3, A4]
X =  [1/4, 1/2, 3/4]
length_X = len(X)
# 4 - количество методов
res = np.zeros((length_X, 4))
for j in range(4):
    for k in range(length_X):
        for i in range(len(A[j])):
            if A[j][i] == 0:
                continue
            res[k][j] += A[j][i] * fi(X[k], i+1)
      
print("\nЗначения в точках: ", X, "\n  Кол.     ИМНК     ДМНК      Гал.")
np.set_printoptions(suppress = True, precision = 5, floatmode = "fixed")
print(res)

# графики решения
def solution(A, x):
    y = 0
    for i in range(len(A)):
        y += A[i] * fi(x, i+1)
    return y

def y_fun1(x):
    return solution(A1, x)

def y_fun2(x):
    return solution(A2, x)

def y_fun3(x):
    return solution(A3, x)

def y_fun4(x):
    return solution(A4, x)

def print_solution():

    xlist = np.linspace(left, right, 20)
    ylist1 = [y_fun1(x) for x in xlist]
    ylist2 = [y_fun2(x) for x in xlist]
    ylist3 = [y_fun3(x) for x in xlist]
    ylist4 = [y_fun4(x) for x in xlist]
    #ylist_real = [np.sin(x)/np.sin(1) - x for x in xlist]    #for TEST

    fig = plt.figure()

    #plt.plot(xlist, ylist_real, 'yellow', label='Solution')  #for TEST
    plt.plot(xlist, ylist1, 'r:', label='K')
    plt.plot(xlist, ylist2, 'g:', label='I')
    plt.plot(xlist, ylist3, 'b:', label='D')
    plt.plot(xlist, ylist4, 'black', linestyle=':', label='G')
    
    plt.legend(loc='best')
    plt.show()

print_solution()

# for TEST сравнение графиков методов с точным решением
'''def plot_test():

    xlist = np.linspace(left, right, 20)
    y1 = [y_fun1(x) for x in xlist]
    y2 = [y_fun2(x) for x in xlist]
    y3 = [y_fun3(x) for x in xlist]
    y4 = [y_fun4(x) for x in xlist]
    y = [np.sin(x)/np.sin(1) - x for x in xlist]   #for TEST

    fig = plt.figure()
    #subplot 1
    sp = plt.subplot(221)
    plt.plot(xlist, y, 'yellow', label='Solution')
    plt.plot(xlist, y1, 'r:', label='K')
    plt.legend(loc='best')
    #subplot 2
    sp = plt.subplot(222)
    plt.plot(xlist, y, 'yellow', label='Solution')
    plt.plot(xlist, y2, 'g:', label='I')
    plt.legend(loc='best')
    #subplot 3
    sp = plt.subplot(223)
    plt.plot(xlist, y, 'yellow', label='Solution')
    plt.plot(xlist, y3, 'b:', label='D')
    plt.legend(loc='best')
    #subplot 4
    sp = plt.subplot(224)
    plt.plot(xlist, y, 'yellow', label='Solution')
    plt.plot(xlist, y4, 'black', linestyle=':', label='G')
    plt.legend(loc='best')
    plt.show()

plot_test()'''

# невязка методов
'''D1 = Dis.discrepancy(my_F(A1, fi, P, Q), F, left, right, P, Q)
print("\nНевязка метода коллокаций: {:}".format(D1))
D2 = Dis.discrepancy(my_F(A2, fi, P, Q), F, left, right, P, Q)
print("Невязка интегрального МНК: {:}".format(D2))
D3 = Dis.discrepancy(my_F(A3, fi, P, Q), F, left, right, P, Q)
print("Невязка дискретного МНК:   {:}".format(D3))
D4 = Dis.discrepancy(my_F(A4, fi, P, Q), F, left, right, P, Q)
print("Невязка метода Галеркина:  {:}".format(D4))'''

# погрешность методов
razn_F = F - my_F(A1, fi, P, Q)
E1 = error(razn_F, L(razn_F, P, Q), left, right)
print("\nПогрешность метода коллокаций: {:}".format(E1))
razn_F = F - my_F(A2, fi, P, Q)
E2 = error(razn_F, L(razn_F, P, Q), left, right)
print("Погрешность интегрального МНК: {:}".format(E2))
razn_F = F - my_F(A3, fi, P, Q)
E3 = error(razn_F, L(razn_F, P, Q), left, right)
print("Погрешность дискретного МНК:   {:}".format(E3))
razn_F = F - my_F(A4, fi, P, Q)
E4 = error(razn_F, L(razn_F, P, Q), left, right)
print("Погрешность метода Галеркина:  {:}".format(E4))


######################################## for Test1 #####################################
# сравнение результатов дискретного МНК при разном значении N - кол-во слагаемых
'''def discrete(P, Q, F, n, N, left, right, fi):
    print("\n\nДискретный МНК:\n" + '-'*70)
    print("N = ", N)
    A3 = DLSM.discrete_LSM(P, Q, F, n, N, left, right, fi)
    print_res(n, A3, fi)
    return A3

N_disc = [2, 3, 4, 5, 10, 50, 100]
A_disc = []
len_N_disc = len(N_disc)
for i in range(len_N_disc):
    A_disc.append(discrete(P, Q, F, n, N_disc[i], left, right, fi))

len_A_disc = len(A_disc)

print("\nСравнение\n", '-'*70)
for i in range(len_N_disc):
    print("N = ", N_disc[i], ":  A = ", A_disc[i])

X_disc =  [1/4, 1/2, 3/4]
len_X_disc = len(X_disc)

res_disc = np.zeros((len_X_disc,len_A_disc))
for i in range(len_A_disc):
    for j in range(len_X_disc):
        for k in range(len(A_disc[i])):
            if A_disc[i][k] == 0:
                continue
            res_disc[j][i] += A_disc[i][k] * fi(X_disc[j], k+1)
      
print("\nЗначения в точках: ", X_disc)
print("N =", N_disc)
np.set_printoptions(suppress = True, precision = 5, floatmode = "fixed")
print(res_disc)'''

######################################## for Test2 #####################################
# Сравнение результатов метода Галеркина при различном количестве базисных функций 
'''def galerkin(P, Q, F, n, left, right, fi):
    print("\n\nМетод Галеркина:\n" + '-'*70)
    print("n = ", n)
    A4 = GM.galerkin_method(P, Q, F, n, left, right, fi)
    print_res(n, A4, fi)
    return A4

#n_gal = [2, 5, 10, 20, 25, 30]
n_gal = [25, 26, 27, 28, 29, 30]
A_gal = []
len_n_gal = len(n_gal)
for i in range(len_n_gal):
    A_gal.append(galerkin(P, Q, F, n_gal[i], left, right, fi))

len_A_gal = len(A_gal)

print("\nСравнение\n", '-'*70)
for i in range(len_n_gal):
    print("n = ", n_gal[i], ":  A = ", A_gal[i])

X_gal =  [1/4, 1/2, 3/4]
len_X_gal = len(X_gal)

res_gal = np.zeros((len_X_gal,len_A_gal))
for i in range(len_A_gal):
    for j in range(len_X_gal):
        for k in range(len(A_gal[i])):
            if A_gal[i][k] == 0:
                continue
            res_gal[j][i] += A_gal[i][k] * fi(X_gal[j], k+1)
      

for i in range(len_X_gal):
    print("\nЗначения в точке: ", X_gal[i])
    for j in range(len(res_gal[i])):
        print("n = {:4d}      ".format(n_gal[j]), res_gal[i][j])'''



