import numpy as np
from numpy.polynomial import Polynomial as P

def Sturm_Method(p, a, b):
    prevprev = p
    prev = p.deriv(1)           # первая производня полинома
    countx = county = 0         # количество смен знака на концах отрезка 

    # считаем количество смен знака на концах отрезка (для исходного полинома и его производной)
    prevx = prevprev(a)
    prevy = prevprev(b)
    x = prev(a)
    y = prev(b)
    
    # если значение от конца отрезка 0.0 (особая логика подсчета смены знака)
    if (x * prevx < 0):
        countx += 1
    elif (x * prevx == 0):
        if (x == 0):
            if (prevx < 0):
                countx += 1
        else:
            if (x < 0):
                countx += 1
    if (y * prevy < 0):
        county += 1
    elif (y * prevy == 0):
        if (y == 0):
            if (prevy < 0):
                county += 1
        else:
            if (y < 0):
                county += 1

    print("Ряд Штурма и значения на концах отрезка:\n\nf0 = " + str(p))
    print('f0({:}) = {:<20} \t\t f0({:}) = {:<20} \n'.format(a, prevx, b, prevy))
    print("f1 = " + str(prev))
    print('f1({:}) = {:<20} \t\t f1({:}) = {:<20} \n'.format(a, x, b, y))

    i = 2                       # счетчик для красивого вывода в цикле
    while (prev.degree() > 0):
        #  остаток от деления, взятый с обратным знаком
        now = -1 * (prevprev % prev)      
        prevprev = prev
        prev = now
        # считаем количество смен знака на концах отрезка
        prevx = x
        prevy = y
        x = prev(a)
        y = prev(b)
        # если значение от конца отрезка 0.0 (особая логика подсчета смены знака)
        if (x * prevx < 0):
            countx += 1
        elif (x * prevx == 0):
            if (x == 0):
                if (prevx < 0):
                    countx += 1
            else:
                if (x < 0):
                    countx += 1
        if (y * prevy < 0):
            county += 1
        elif (y * prevy == 0):
            if (y == 0):
                if (prevy < 0):
                    county += 1
            else:
                if (y < 0):
                    county += 1
        print("f" + str(i) + " = " + str(prev))
        print('f{:}({:}) = {:<20} \t\t f{:}({:}) = {:<20} \n'.format(i, a, x, i, b, y))
        i += 1

    # количество корней по теореме Штурма
    N = countx - county
    print("Количество корней по теореме Штурма: N = " + str(N))
    return N


     


