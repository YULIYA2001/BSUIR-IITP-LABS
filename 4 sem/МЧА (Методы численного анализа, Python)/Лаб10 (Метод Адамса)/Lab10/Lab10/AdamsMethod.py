import numpy as np

def adams_method(f, a, b, y0, h):
    '''Метод Адамса с заданным шагом h'''
    x = np.arange(a, b+1e-10, h)
    y = np.zeros(len(x))
    y[0] = y0
    y[1] = runge_kutta_find_y1(f, a, b, y0, h)
    for i in range(1, len(x)-1):
        y[i+1] = y[i] + (3/2 * f(x[i], y[i]) - 1/2 * f(x[i-1], y[i-1])) * h
    return x, y

def runge_kutta_find_y1(f, a, b, y0, h):
    '''Упрощенный метод Рунге-Кутта 4-го порядка с заданным шагом h, который ищет только значение в точке y1'''
    x0 = a
    K1 = h * f(x0, y0)
    K2 = h * f(x0 + h/2, y0 + K1/2)
    K3 = h * f(x0 + h/2, y0 + K2/2)
    K4 = h * f(x0 + h, y0 + K3)
    y1 = y0 + (K1 + 2*K2 + 2*K3 + K4)/6
    return y1

def adams_method_eps(f, a, b, y0, h, eps):
    '''Метод Адамса с заданной точностью eps и начальным шагом h'''
    x, y = adams_method(f, a, b, y0, h)
    E = 1
    while True:
        nextx, nexty = adams_method(f, a, b, y0, h/2)
        difference = np.zeros(len(x))
        for i in range (len(x)):
            difference[i] = abs(y[i] - nexty[2*i])
        if max(difference) < eps:
            break
        h = h/2
        x, y = nextx, nexty
    return x, y, h

def error(f, a, b, y0, h):
    '''Погрешность метода Адамса с заданным шагом'''
    x, y = adams_method(f, a, b, y0, h)
    nextx, nexty = adams_method(f, a, b, y0, h/2)
    difference = np.zeros(len(x))
    for i in range (len(x)):
        difference[i] = abs(y[i] - nexty[2*i])
    return max(difference)