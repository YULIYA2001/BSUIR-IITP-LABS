import numpy as np
import math
import scipy.interpolate
# для проверки графически
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt
# метод прогонки 
import Spline3Interpolation as SpI

'''
# тестовый пример
def f(x):
    return np.cos(x)
a = 0
b = 1
n = 5
x = 0.5*(b - a)
y = 0.8776
'''

# условие (вариант 5)
def f(x):
    return np.sinh(x)

a = 0
b = 2
n = 6
x = 0.5*(b - a)
y = 1.1752

# выберем равномерный шаг
h = (b - a)/(n - 1)

# массивы точек х и соответствующих им значений у
xi = np.zeros(n);
xi[0] = a 
for i in range(1, n):
    xi[i] = xi[i - 1] + h
yi = np.zeros(n)
for i in range(n):
    yi[i] = f(xi[i])

print("~~~~~~~~~~~~~~~~~~~~~~~~~~~ Интерполяция сплайнами ~~~~~~~~~~~~~~~~~~~~~~~~\n\n\t\t\t\t Вариант 5")
print("Исходные данные: \n  функция: sh(x) \n  интервал: [{:}, {:}]\n  число узлов: {:}".format(a, b, n),
    "\n  значение в точке х = {:}: y = {:}".format(x, y))
np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")
print("\nМассив точек х = ", xi)
print("Массив точек у = ",yi)

Sx = SpI.spline_method(xi, yi, n-1, x, h)

print("\nЗначение сплайна в точке х = {:} равно".format(x), "%.6f" % Sx)

# проверка встроенным методом
tck = scipy.interpolate.splrep(xi, yi)
print("\nПроверка встроенным методом: f({:}) = ".format(x), "%.6f" % scipy.interpolate.splev(x, tck))

print("Погрешность: ", abs(f(x) - Sx))

# встроенный график сплайна
cs = CubicSpline(xi, yi, bc_type='natural')
X = np.linspace(a, b, 100)
Y = [cs(xi) for xi in X]
plt.plot(X, Y, color = 'yellow')
# график по функции spline_method() 
X = np.linspace(a, b, 100)
Y2 = [SpI.spline_method(xi, yi, n-1, x, h) for x in X]
plt.plot(X, Y2, ':', color = 'r')
plt.show()