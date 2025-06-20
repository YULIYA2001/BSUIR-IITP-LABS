import numpy as np
import SimpleIterationMethod as SIM
import NewtonMethod as NM
# Для графика
from sympy import plot_implicit, symbols, Eq, tan

# Графики функций
x, y = symbols('x y')
# исходные функции
expr1 = tan(x * y + 0.2) - x
expr2 = 0.9 * x ** 2 + 2 * y ** 2 - 1
'''
################# Test #####################
expr1 = x + 2 * y - 2
expr2 = x ** 2 + 2 * y ** 2 - 2
x0 = 0.01
y0 = 0.99
############################################
'''
p1 = plot_implicit(Eq(expr1, 0), (x, -1.5, 1.5), (y, -1.5, 1.5), show = False, line_color='yellow')
p2 = plot_implicit(Eq(expr2, 0), (x, -1.5, 1.5), (y, -1.5, 1.5), show = False, line_color='red')
p1.extend(p2)
p1.show()

# Начальное приближение
x0 = 0.6
y0 = 0.6

eps = 0.0001

print(82 * "-")
print("|                                    Вариант 5                                   |")
print(82 * "-")
print("Начальные условия: ")
print(expr1, " = 0")
print(expr2, " = 0")
print("\nНачальное приближение: x0 = {:<5} y0 = {:<5}".format(x0, y0))

print("\n\t\t\tМетод простых итераций:\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~\n")
SIM.Simple_Iteration_Method(x0, y0, eps)
print("\n\t\t\t\tМетод Ньютона:\n\t\t\t\t~~~~~~~~~~~~~~\n")
NM.Newton_Method(x0, y0, eps)

