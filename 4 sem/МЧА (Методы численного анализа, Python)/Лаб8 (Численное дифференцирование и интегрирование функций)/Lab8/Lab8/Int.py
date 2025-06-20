import numpy as np

def integrate_rect(method, func, a, b, n):
    '''Метод прямоугольников, n (число отрезков разбиения) задается вручную.'''
    h = (b - a) / n
    intF = 0.0
    if method == 'right':
        for x in np.arange(a+h, b+h, h):
            intF += func(x)
    elif method == 'left':
        for x in np.arange(a, b, h):
            intF += func(x)
    elif method == 'central':
        for x in np.arange(a, b, h):
            intF += func(x + h/2)
    intF *= h
    return intF

def rectangles(method, func, a, b, eps, real_integral):
    '''Метод прямоугольников, n (число отрезков разбиения) высчитывается исходя из погешности (правило Рунге).'''
    # правило Рунге
    E, n = 1, 2
    while abs(E) > eps:
        E = (integrate_rect(method, func, a, b, n * 2) - integrate_rect(method, func, a, b, n)) / 3
        n *= 2

    if method == 'right':
        print("\n\nФормула правых прямоугольников: int f(x) = h*(y(1) + y(2) + ... + y(n)")
    elif method == 'left':
        print("\n\nФормула левых прямоугольников: int f(x) = h*(y(0) + y(1) + ... + y(n-1)")
    elif method == 'central':
        print("\n\nФормула средних прямоугольников: int f(x) = h*(f(x0 + h/2) + f(x1 + h/2) ",
            "+ ... + f(x(n-1) + h/2)")
    print("--------------------------------------------------------------------------")
    print("Число отрезков разбиения:", n, "\nШаг: ", (b - a) / n)
    print("По формуле      int(y) = ", integrate_rect(method, func, a, b, n))
    print("Точное значение int(y) = ", real_integral)
    print("Требуемая погрешность: ", eps)
    print("Погрешность: ", abs(E))


def integrate_trapez(func, a, b, n):
    '''Метод трапеций, n (число отрезков разбиения) задается вручную.'''
    h = (b - a) / n
    intF = (func(a) + func(b))/2
    for x in np.arange(a+h, b, h):
        intF += func(x)
    intF *= h
    return intF

def trapezium(func, a, b, eps, real_integral):
    '''Метод трапеций, n (число отрезков разбиения) высчитывается исходя из погешности (правило Рунге).'''
    E, n = 1, 2
    while abs(E) > eps:
        E = (integrate_trapez(func, a, b, n * 2) - integrate_trapez(func, a, b, n)) / 3
        n *= 2

    print("\n\nФормула трапеций: int f(x) = h*((y(0)+y(n))/2 + y(1) +... + y(n-1)")
    print("----------------------------------------------------------------------")
    print("Число отрезков разбиения:", n, "\nШаг: ", (b - a) / n)
    print("По формуле      int(y) = ", integrate_trapez(func, a, b, n))
    print("Точное значение int(y) = ", real_integral)
    print("Требуемая погрешность: ", eps)
    print("Погрешность: ", abs(E))
    

def integrate_Sim(func, a, b, n):
    '''Метод Симпсона, n (число отрезков разбиения) задается вручную.'''
    if n % 2 != 0:
        n += 1
    h = (b - a) / 2/n

    subsum1_intF, subsum2_intF = 0.0, 0.0
    for x in np.arange(a + 2*h, b - h, 2*h):
        subsum1_intF += func(x)
    for x in np.arange(a + h, b, 2*h):
        subsum2_intF += func(x)

    intF = h*(func(a) + func(b) + 2*subsum1_intF + 4*subsum2_intF)/3
    return intF

def simpson(func, a, b, eps, real_integral):
    '''Метод Симпсона, n (число отрезков разбиения) высчитывается исходя из погешности (правило Рунге).'''
    E, n = 1, 2
    while abs(E) > eps:
        E = (integrate_Sim(func, a, b, n * 2) - integrate_Sim(func, a, b, n)) / 15
        n *= 2

    print("\n\nФормула Симпсона: int f(x) = h*((y(0)+y(n))/2 + y(1) +... + y(n-1)")
    print("----------------------------------------------------------------------")
    print("Число отрезков разбиения:", n, "\nШаг: ", (b - a) / 2/n)
    print("По формуле      int(y) = ", integrate_Sim(func, a, b, n))
    print("Точное значение int(y) = ", real_integral)
    print("Требуемая погрешность: ", eps)
    print("Погрешность: ", abs(E))







    