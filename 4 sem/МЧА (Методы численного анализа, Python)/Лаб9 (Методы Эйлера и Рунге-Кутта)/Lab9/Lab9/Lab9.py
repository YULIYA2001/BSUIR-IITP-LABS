import numpy as np
from EulerMethod import *
from RungeKuttaMethod import *
import matplotlib.pyplot as plt

# условие (вариант 5)
def diff_y(x, y, a, m):
    return a*(1 - y**2)/((1 + m) * x**2 + y**2 + 1)

def diff_y5(x, y):
    a = 1.3
    m = 1.5
    return diff_y(x, y, a, m)

A = 0
B = 1
eps = 0.001
x0, y0 = 0, 0
m = 1.5
a = 1.3


################################### ВЫВОД ИСХОДНЫХ ДАННЫХ #######################################

print("~~~~~~~~~ Методы Эйлера и Рунге-Кутта ~~~~~~~~\n\n\t\t\t\t Вариант 5")
print("Исходные данные: \n",
      "уравнение: y' = ", a, "*(1 - y^2)/(", 1+m, "*x^2 + y^2 + 1) \n",
      "интервал: [{:}, {:}]\n".format(A, B),
      "точность: {:}\n".format(eps),
      "начальные условия: y({:}) = {:}\n".format(x0, y0))



########################## ГРАФИК И РЕШЕНИЕ - ЗНАЧЕНИЕ ШАГА (ВАРИАНТ 5) ##########################

# start_h ^ 4 < eps условие для метода Рунге-Кутта
start_h = 0.1
x, y, h = euler_method_eps(diff_y5, A, B, y0, start_h, eps)
xm, ym, hm = euler_modified_eps(diff_y5, A, B, y0, start_h, eps)
xrk, yrk, hrk = runge_kutta_method_eps(diff_y5, A, B, y0, start_h, eps)
#plt.plot(x, y, 'r-', xm, ym, 'b:', xrk, yrk, 'g:')
#plt.legend(['Euler', 'Modified Euler', 'Runge-Kutta'])
#plt.grid(True)
#plt.title("Solution of $y'=1.3*(1 - y^2)/(2.5*x^2 + y^2 + 1), y(0)=0$")
#plt.show()


plt.figure(figsize = (10, 7))
#subplot 1
plt.subplot(221)
plt.plot(x, y, 'r:')
plt.legend(['Euler'])
plt.grid(True)
#subplot 2
plt.subplot(222)
plt.plot(xm, ym, 'c:')
plt.legend(['Modified Euler'])
plt.grid(True)
#subplot 3
plt.subplot(223)
plt.plot(xrk, yrk, 'k:')
plt.legend(['Runge-Kutta'])
plt.grid(True)
#subplot 4
plt.subplot(224)
plt.plot(x, y, 'r-', xm, ym, 'c--', xrk, yrk, 'k:')
plt.title("Solution of $y'=1.3*(1 - y^2)/(2.5*x^2 + y^2 + 1), y(0)=0$")
plt.legend(['Euler', 'Modified Euler', 'Runge-Kutta'])
plt.grid(True)
plt.show()



print("Метод Эйлера. Точность eps = {:} достигнута при значении шага h = {:}".format(eps, h))
print("Модифицированный метод Эйлера. Точность eps = {:} достигнута при значении шага h = {:}".format(eps, hm))
print("Метод Рунге-Кутта. Точность eps = {:} достигнута при значении шага h = {:}".format(eps, hrk))



########################## СРАВНЕНИЕ МЕТОДОВ ДЛЯ КОНКРЕТНОГО ШАГА (ВАРИАНТ 5) ##########################

# чтобы наглядно видеть таблицу, значение my_h следует брать небольшим
my_h = 0.1      
print("\n\n~~~~~~~~~~~~~~~ Сравнение методов для шага ", my_h, "~~~~~~~~~~~~~~~~~~~~~~\n\nТаблица значений\n")

x, y = euler_method(diff_y5, A, B, y0, my_h)
xm, ym = euler_modified(diff_y5, A, B, y0, my_h)
xrk, yrk = runge_kutta_method(diff_y5, A, B, y0, my_h)

# таблица значений решения ОДУ в точках x, y, ym-(модифицированного метода Эйлера), yrk - (метода Рунге-Кутта)
np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")
print("x:   ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(x[i]), end="")
print("\ny:   ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(y[i]), end="")
print("\nym:  ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(ym[i]), end="")
print("\nyrk: ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(yrk[i]), end="")

print("\n\nПогрешность метода Эйлера: ", error(diff_y5, A, B, y0, my_h, 'euler'))
print("Погрешность модифицированного метода Эйлера: ", error(diff_y5, A, B, y0, my_h, 'euler_m'))
print("Погрешность метода Рунге-Кутта: ", error_rk(diff_y5, A, B, y0, my_h))


'''
####################################### ТЕСТОВЫЙ ПРИМЕР №1 ###########################################

# график тестового примера №1: y'=y^2  y(0)=-1   [0, 3]  h=0.3
def f1(x, y):
    return y**2
a, b, y0, h  = 0, 3, -1, 0.3
x, y = euler_method(f1, a, b, y0, h)
xm, ym = euler_modified(f1, a, b, y0, h)
xrk, yrk = runge_kutta_method(f1, a, b, y0, h)
x_true = np.linspace(a, b, 100)
y_true = -1/(x_true + 1)
plt.plot(x, y, 'g.-', xm, ym, 'y.-', xrk, yrk, 'b.-',x_true, y_true, 'r--')
plt.legend(['Euler', 'Modified Euler', 'Runge-Kutta', 'True'])
plt.grid(True)
plt.title("Solution of $y'=y^2 , y(0)=-1 , [0, 3] , h=0.3$")
plt.show()



########################## ТЕСТОВЫЙ ПРИМЕР №2 (ИЗ МЕТОДИЧКИ) ###########################################

# решение и график тестового примера №2: y'=-y  y(0)=1   [0, 1]  h=0.2
def f2(x, y):
    return -y
a, b, y0, h  = 0, 1, 1, 0.2
x, y = euler_method(f2, a, b, y0, h)
xm, ym = euler_modified(f2, a, b, y0, h)
xrk, yrk = runge_kutta_method(f2, a, b, y0, h)
y_true = np.exp(-x)

plt.figure(figsize = (10, 7))
#subplot 1
plt.subplot(231)
plt.plot(x, y_true, 'y-', x, y, 'g.:')
plt.legend(['True', 'Euler'])
plt.grid(True)
#subplot 2
plt.subplot(232)
plt.plot(x, y_true,'y-', xm, ym, 'r.:')
plt.legend(['True', 'Modified Euler'])
plt.grid(True)
plt.title("Solution of $y'=-y , y(0)=1 , [0, 1] , h=0.2$")
#subplot 3
plt.subplot(233)
plt.plot(x, y_true,'y-', xrk, yrk, 'k.:')
plt.legend(['True', 'Runge-Kutta'])
plt.grid(True)
#subplot 4
plt.subplot(235)
plt.plot(x, y, 'g.:', xm, ym, 'r.:', xrk, yrk, 'k.:', x, y_true,'y:')
plt.legend(['Euler', 'Modified Euler', 'Runge-Kutta', 'True'])
plt.grid(True)
plt.show()


print("x     ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(x[i]), end="")
print("\ny     ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(y[i]), end="")
print("\ny_m   ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(ym[i]), end="")
print("\ny_rk  ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(yrk[i]), end="")
print("\ny_true", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(y_true[i]), end="")
'''