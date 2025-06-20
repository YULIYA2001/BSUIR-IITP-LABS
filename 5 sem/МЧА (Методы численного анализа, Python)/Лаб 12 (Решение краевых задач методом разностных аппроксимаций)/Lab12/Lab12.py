import numpy as np 
import sympy as sp 
import matplotlib.pyplot as plt
import DifferenceApproximationMethod as DAM
import SweepMethod as SM
import FindHWithEps as FH

import Task1
import Task2
import Task3
import Task4

from scipy import linalg

k = 3
print("ЛР 11. Решение краевых задач методом разностных аппроксимаций\n")
print("\t\t\tВариант {0}".format(k))
print("-" * 50)


########################################################
'''
# Test1 y" + y = -x
def p(x):
   return 0
def q(x):
    return 1
def f(x):
    return -x
left = 0
right = 1
y0 = yn = 0
eps = 0.00001
print("eps = ", eps)

h = 0.5
print("Начальный шаг: h = ", h)
h, n, X = FH.find_h(h, right, left, p, q, f, y0, yn, eps, False)
y_test = SM.sweep_method_for_diff(p, q, f, h, n, X, y0, yn, False)
fig = plt.figure()
y = [np.sin(x)/np.sin(1) - x for x in X]
plt.plot(X, y, 'yellow', label='RealSolution')
plt.plot(X, y_test, 'r:', label='MySolution')
plt.legend(loc='best')
plt.show()

s = 0
for i in range(len(y)):
    s += (y[i] - y_test[i]) * (y[i] - y_test[i])
s = np.sqrt(s/len(y))
print("S = ", s)
'''
#############################################################
'''
# Test2 y" - y = x
def p(x):
   return 0
def q(x):
    return -1
def f(x):
    return x
left = 0
right = 1
y0 = yn = 0
eps = 0.0009
print("eps = ", eps)

h = 0.4
print("Начальный шаг: h = ", h)
h, n, X = FH.find_h(h, right, left, p, q, f, y0, yn, eps, False)
y_test = SM.sweep_method_for_diff(p, q, f, h, n, X, y0, yn, True)
fig = plt.figure()
X_ = np.linspace(left, right, n*4+1) 
y = [-np.exp(-x)/(np.exp(1) - np.exp(-1)) + np.exp(x)/(np.exp(1) - np.exp(-1)) - x  for x in X_]
plt.plot(X_, y, 'yellow', label='RealSolution')
plt.plot(X, y_test, 'r:', label='MySolution')
plt.legend(loc='best')
plt.show()

s = 0
for i in range(len(y_test)):
    s += (y[i*4] - y_test[i]) * (y[i*4] - y_test[i])
s = np.sqrt(s/len(y_test))
print("S = ", s)
'''
#############################################################


def print_array(y):
    for i in range(len(y)):
        print("{:.6f}".format(y[i]), end="  ")
    print()

def plot_res(y1, y2, label1, label2, X): 
    fig = plt.figure()
    plt.plot(X, y1, 'yellow', label=label1)
    plt.plot(X, y2, 'r:', label=label2)

    # for test
    #y = [np.sin(x)/np.sin(1) - x for x in X]
    #plt.plot(X, y, 'b:', label='RealSolution')

    plt.legend(loc='best')
    plt.show()

##############################################################

# TASK 1 ########
#Task1.task1()

# TASK 2 ########
#Task2.task2()

# TASK 3 ########
#Task3.task3()

# TASK 4 ########
Task4.task4()



