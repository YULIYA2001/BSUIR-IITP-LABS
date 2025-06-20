import numpy as np
from AdamsMethod import *
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

print("~~~~~~~~~~~~~~~~~~~~~~ Метод Адамса ~~~~~~~~~~~~~~~~~~~~~~\n\n\t\t\t Вариант 5")
print("Исходные данные: \n",
      "уравнение: y' = ", a, "*(1 - y^2)/(", 1+m, "*x^2 + y^2 + 1) \n",
      "интервал: [{:}, {:}]\n".format(A, B),
      "точность: {:}\n".format(eps),
      "начальные условия: y({:}) = {:}\n".format(x0, y0))



########################## ГРАФИК И РЕШЕНИЕ - ЗНАЧЕНИЕ ШАГА (ВАРИАНТ 5) ##########################
start_h = 0.3
x, y, h = adams_method_eps(diff_y5, A, B, y0, start_h, eps)
print("Метод Адамса.\n----------------")
print("С начальным шагом {:} точность eps = {:} достигнута при значении шага h = {:}".
      format(start_h, eps, h), " (точность при этом шаге {:.7f})".format(error(diff_y5, A, B, y0, h), h))

my_h = 0.2
x1, y1 = adams_method(diff_y5, A, B, y0, my_h)

plt.plot(x, y, 'r.-', x1, y1, 'k--')
plt.legend(['step={:}'.format(h), 'step={:}'.format(my_h)])
plt.grid(True)
plt.title("Решение уравнения $y'=1.3*(1 - y^2)/(2.5*x^2 + y^2 + 1), y(0)=0$")
plt.show()

x, y = adams_method(diff_y5, A, B, y0, 0.045)
print("\nЭксперементально найден более точный (для данной погрешности) шаг h = 0.045, дает погрешность {:.7f}".
      format(error(diff_y5, A, B, y0, 0.045)))
plt.plot(x, y, 'g.-')
plt.legend(['Adams method step=0.045'])
plt.grid(True)
plt.title("Решение уравнения $y'=1.3*(1 - y^2)/(2.5*x^2 + y^2 + 1), y(0)=0$")
plt.show()

# таблица значений метода Адамса и реальных значений
#np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")
#for i in range(len(x)):
#    print("{:.4f} | {:.4f}".format(x[i], y[i]), end="\n")

'''
####################################### ТЕСТОВЫЙ ПРИМЕР №1 ###########################################

# график тестового примера №1: y'=y^2  y(0)=-1   [0, 3]  h=0.3
def f1(x, y):
    return y**2
a, b, y0, h  = 0, 3, -1, 0.3
x, y = adams_method(f1, a, b, y0, h)

h2 = 0.01
x2, y2 = adams_method(f1, a, b, y0, h2)

x_true = np.linspace(a, b, 100)
y_true = -1/(x_true + 1)
plt.plot(x, y, 'g.-', x2, y2, 'b-', x_true, y_true, 'r--')
plt.legend(['Adams method step={:}'.format(h),'Adams method step={:}'.format(h2), 'True'])
plt.grid(True)
plt.show()

print("\nТЕСТОВЫЙ ПРИМЕР №2: y'=-y  y(0)=1   [0, 1]  h=0.2")
print("-------------------------------------------------")
print("Погрешность метода Адамса h = 0.3: ", error(f1, a, b, y0, h))
print("Погрешность метода Адамса h = 0.01: ", error(f1, a, b, y0, h2))



########################## ТЕСТОВЫЙ ПРИМЕР №2 (ИЗ МЕТОДИЧКИ) ###########################################

# решение и график тестового примера №2: y'=-y  y(0)=1   [0, 1]  h=0.2
def f2(x, y):
    return -y
a, b, y0, h  = 0, 1, 1, 0.2
x, y = adams_method(f2, a, b, y0, h)
y_true = np.exp(-x)

plt.plot(x, y, 'r.-', x, y_true,'b--')
plt.legend(['Adams', 'True'])
plt.grid(True)
plt.show()

print("\nТЕСТОВЫЙ ПРИМЕР №2: y'=-y  y(0)=1   [0, 1]  h=0.2")
print("-------------------------------------------------")
# таблица значений метода Адамса и реальных значений
np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")
print("x      ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(x[i]), end="")
print("\ny_adams", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(y[i]), end="")
print("\ny_true ", end=" | ")
for i in range(len(x)):
    print("{:.4f} | ".format(y_true[i]), end="")

print("\nПогрешность метода Адамса: ", error(f2, a, b, y0, h))
'''