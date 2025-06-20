import numpy as np

def runge_kutta_method(f, a, b, y0, h):
    '''Метод Рунге-Кутта с заданным шагом h'''
    x = np.arange(a, b+h/2, h)
    y = np.zeros(len(x))
    y[0] = y0
    for i in range(0, len(x)-1):
        K1 = h * f(x[i], y[i])
        K2 = h * f(x[i] + h/2, y[i] + K1/2)
        K3 = h * f(x[i] + h/2, y[i] + K2/2)
        K4 = h * f(x[i] + h, y[i] + K3)
        y[i+1] = y[i] + (K1 + 2*K2 + 2*K3 + K4)/6
    return x, y

def runge_kutta_method_eps(f, a, b, y0, h, eps):
    '''Метод Рунге-Кутта с заданной точностью eps и начальным шагом h'''
    x, y = runge_kutta_method(f, a, b, y0, h)
    E = 1
    while True:
        nextx, nexty = runge_kutta_method(f, a, b, y0, h/2)
        difference = np.zeros(len(x))
        for i in range (len(x)):
            difference[i] = abs(y[i] - nexty[2*i])
        if max(difference) < eps:
            break
        h = h/2
        x, y = nextx, nexty
    return x, y, h

def error_rk(f, a, b, y0, h):
    x, y = runge_kutta_method(f, a, b, y0, h)
    nextx, nexty = runge_kutta_method(f, a, b, y0, h/2)
    difference = np.zeros(len(x))
    for i in range (len(x)):
        difference[i] = abs(y[i] - nexty[2*i])
    return max(difference)