import numpy as np

def euler_method(f, a, b, y0, h):
    '''Метод Эйлера с заданным шагом h'''
    x = np.arange(a, b+h/2, h)
    y = np.zeros(len(x))
    y[0] = y0
    for i in range(0, len(x)-1):
        y[i+1] = y[i] + f(x[i], y[i])*h
    return x, y

def euler_method_eps(f, a, b, y0, h, eps):
    '''Метод Эйлера с заданной точностью eps и начальным шагом h'''
    x, y = euler_method(f, a, b, y0, h)
    E = 1
    while True:
        nextx, nexty = euler_method(f, a, b, y0, h/2)
        difference = np.zeros(len(x))
        for i in range (len(x)):
            difference[i] = abs(y[i] - nexty[2*i])
        if max(difference) < eps:
            break
        h = h/2
        x, y = nextx, nexty
    return x, y, h

def euler_modified(f, a, b, y0, h):
    '''Модифицированный метод Эйлера с заданным шагом h'''
    x = np.arange(a, b+h/2, h)
    y = np.zeros(len(x))
    y[0] = y0
    for i in range(0, len(x)-1):
        y[i+1] = y[i] + f(x[i] + h/2, y[i] + h/2*f(x[i], y[i]))*h
    return x, y

def euler_modified_eps(f, a, b, y0, h, eps):
    '''Модифицированный метод Эйлера с заданной точностью eps и начальным шагом h'''
    x, y = euler_modified(f, a, b, y0, h)
    E = 1
    while True:
        nextx, nexty = euler_modified(f, a, b, y0, h/2)
        difference = np.zeros(len(x))
        for i in range (len(x)):
            difference[i] = abs(y[i] - nexty[2*i])
        if max(difference) < eps:
            break
        h = h/2
        x, y = nextx, nexty
    return x, y, h

def error(f, a, b, y0, h, method):
    if method == 'euler_m':
        x, y = euler_modified(f, a, b, y0, h)
        nextx, nexty = euler_modified(f, a, b, y0, h/2)
    elif method == 'euler':
        x, y = euler_method(f, a, b, y0, h)
        nextx, nexty = euler_method(f, a, b, y0, h/2)
    difference = np.zeros(len(x))
    for i in range (len(x)):
        difference[i] = abs(y[i] - nexty[2*i])
    return max(difference)

