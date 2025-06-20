import numpy as np
from numpy.polynomial import Polynomial as P
import SturmMethod as SM
import SeparateRoots as SR
import HalfDivisionMethod as DM
import HordeMethod as HM
import NewtonMethod as NM
# Для графика
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

p = P([773.65, -243.672, 9.57496, 1]) 
left = -10
right = 10
step = 20.0             # шаг для отделения корней

# тестовые примеры
#p = P([-1.0, 1.0, 3.0, 2.0]) 
#left = 0
#right = 1
#step = 1.0

#p = P([-1.0, 0.0, -1.0, 1.0])   
#left = 1
#right = 2
#step = 1.0

eps = 0.0001

# График функции
fig, ax = plt.subplots()
x = np.linspace(-10, 10, 200)
y = 773.65 - 243.672 * x ** 1 + 9.57496 * x ** 2 + 1.0 * x ** 3
ax.plot(x, y, c = "r")
ax.xaxis.set_major_locator(ticker.MultipleLocator(2))           # Установить интервал основных
ax.xaxis.set_minor_locator(ticker.MultipleLocator(1))           # и вспомогательных делений
ax.grid(which='major', color = 'k')                             # Добавить линии основной сетки
ax.minorticks_on()                                              # Включить видимость вспомогательных делений
ax.grid(which='minor', color = 'gray', linestyle = ':')         # Задать внешний вид вспомогательной сетки
plt.show()


print(82 * "-")
print("|                                    Вариант 5                                   |")
print(82 * "-")
print("\n\t\t 1) Определение количества корней методом Штурма:")
print("\t\t-----------------------------------------------\n")
count = SM.Sturm_Method(p, left, right)
if (count != 0):
    print("\n\n\t\t\t\t2)Отделение корней:")
    print("\t\t-----------------------------------------------\n")
    root_interval = SR.Separate_Roots(p, left, right, step, count)

    l = root_interval[0]
    r = root_interval[0] + root_interval[root_interval.size - 1]
    print("\n\n\t\t\t3)Вычисление наименьшего из корней:")
    print("\t\t-----------------------------------------------\n")
    print("\n\t\t\tМетод половнного деления:\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~\n")
    DM.Half_Division_Method(p, l, r, eps)
    print("\n\t\t\t\t  Метод хорд:\n\t\t\t\t  ~~~~~~~~~~~\n")
    HM.Horde_Method(p, l, r, eps)
    print("\n\t\t\t\tМетод Ньютона:\n\t\t\t\t~~~~~~~~~~~~~~\n")
    NM.Newton_Method(p, l, r, eps)
 



