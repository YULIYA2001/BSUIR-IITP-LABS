import numpy as np
from Diff import *
from Int import *
import matplotlib.pyplot as plt

# условие (вариант 5)
def func(x):
    return np.sqrt(np.tan(x)) 

def diff_func(x):
    return (1 + np.tan(x)**2) / (2 * np.sqrt(np.tan(x)))

def diff_2_func(x):
    return (-4 * np.cos(x)**2 + 3) / (4 * np.cos(x)**3 * np.sin(x) * np.sqrt(np.sin(x) / np.cos(x)))

a = 0
b = 1.5
eps_diff = 0.01
eps_int = 0.000001
real_integral = 1.689378830261396

#середина заданного интервала
x = (b-a) / 2

print("~~~~~~~~~ Численное дифференцирование и интегрирование функций ~~~~~~~~\n\n\t\t\t\t Вариант 5")
print("Исходные данные: \n  функция: √(tg(x))\n  интервал: [{:}, {:}]\n  точность ".format(a, b),
      "дифференцирования: {:}\n  точность интегрирования: {:}\n  значение интеграла: ".format(eps_diff, eps_int),
      "{:}\n  точка - середина заданного интервала: х = {:}\n".format(real_integral, x))
np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")

# n_f - n forward
n_f = 1
while(True):
    h_f = (b - a)/(n_f + 1)
    if abs(derivative(func, x, 'forward', h_f) - diff_func(x)) < eps_diff:
        break
    n_f += 1

print("\n\nФормула:  y' = (y(k+1) - y(k)) / h")
print("----------------------------------")
print("Число отрезков разбиения:", n_f+1, "\nШаг: ", h_f)
print("По формуле      y' = ", derivative(func, x, 'forward', h_f))
print("Точное значение y' = ", diff_func(x))
print("Требуемая погрешность: ", eps_diff)
print("Погрешность: ", derivative(func, x, 'forward', h_f) - diff_func(x))

h_c = (b - a)/(1 + 1)
print(derivative(func, x, 'central', h_c))
h_c = (b - a)/(2 + 1)
print(derivative(func, x, 'central', h_c))
n = 2
# n_c - n central
n_c = 1
while(True):
   h_c = (b - a)/(n_c + 1)
   if abs(derivative(func, x, 'central', h_c) - diff_func(x)) < eps_diff:
       break
   n_c += 1

print("\n\nФормула:  y' = (y(k+1) - y(k-1)) / (2*h)")
print("----------------------------------------")
print("Число отрезков разбиения:", n_c+1, "\nШаг: ", h_c)
print("По формуле      y' = ", derivative(func, x, 'central',h_c))
print("Точное значение y' = ", diff_func(x))
print("Требуемая погрешность: ", eps_diff)
print("Погрешность: ", derivative(func, x, 'central', h_c) - diff_func(x))


# Построение графика первой производной
X = np.linspace(a+0.01, b, 100)
dydxC = derivative(func, X)
dydxF = derivative(func, X, 'forward')
dYdx = diff_func(X)
plt.figure(figsize=(11, 4.5))
plt.subplot(211)
plt.plot(X, dydxC,'g.',label='Central Difference')
plt.plot(X, dYdx,'yellow',label='True Value')
plt.legend(loc='best')
plt.subplot(212)
plt.plot(X, dydxF,'r.',label='Forward Difference')
plt.plot(X, dYdx,'b',label='True Value')
plt.legend(loc='best')
plt.show()


n = 1
while(True):
   h = (b - a)/(n + 1)
   if abs(derivative_2(func, x, h) - diff_2_func(x)) < eps_diff:
       break
   n += 1

print("\n\nФормула:  y\" = (y(k+1) - 2*y(k) + y(k-1)) / (h^2)")
print("--------------------------------------------------")
print("Число отрезков разбиения:", n+1, "\nШаг: ", h)
print("По формуле      y\" =", derivative_2(func, x, h))
print("Точное значение y\" = ", diff_2_func(x))
print("Требуемая погрешность: ", eps_diff)
print("Погрешность: ", derivative_2(func, x, h) - diff_2_func(x))


# Построение графика второй производной
X = np.linspace(a+0.01, b, 100)
dydx = derivative_2(func, X)
dYdx = diff_2_func(X)
plt.plot(X, dydx,'r.',label='Diff 2')
plt.plot(X, dYdx,'b',label='True Value')
plt.legend(loc='best')
plt.show()


################################## ИНТЕГРИРОВАНИЕ #####################################

rectangles('right', func, a, b, eps_int, real_integral)
rectangles('left', func, a, b, eps_int, real_integral)
rectangles('central', func, a, b, eps_int, real_integral)
trapezium(func, a, b, eps_int, real_integral)
simpson(func, a, b, eps_int, real_integral)

# сравнение методов по точности
n = 1000
print("\n\nСравнение методов по точности для числа точек разбиения n = ", n)
print("-----------------------------------------------------------------")
value = integrate_rect('right', func, a, b, n)
print("По формуле правых прямоугольников ", value, 
      "({:})".format(abs(value - integrate_rect('right', func, a, b, n/2)) / 3))

value = integrate_rect('left', func, a, b, n)
print("По формуле левых прямоугольников  ", value, 
      "({:})".format(abs(value - integrate_rect('left', func, a, b, n/2)) / 3))

value = integrate_rect('central', func, a, b, n)
print("По формуле средних прямоугольников", value, 
      "({:})".format(abs(value - integrate_rect('central', func, a, b, n/2)) / 3))

value = integrate_trapez(func, a, b, n)
print("По формуле трапеций               ", value, 
      "({:})".format(abs(value - integrate_trapez(func, a, b, n/2)) / 3))

value = integrate_Sim(func, a, b, n)
print("По формуле Симпсона               ", value, 
      "({:})".format(abs(value - integrate_Sim(func, a, b, n/2)) / 15))

print("Точное значение                   ", real_integral)







