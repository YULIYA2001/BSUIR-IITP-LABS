import numpy as np
from numpy.polynomial import Polynomial as P

def Separate_Roots(p, left, right, step, count):
    # хранит начало интервалов каждого корня и размер шага (в конце)
    root_interval = np.zeros(count + 1)            
    i = 0
    while (True):
        for s in np.arange(left, right, step):
            if (p(s)*p(s + step) < 0):
                root_interval[i] = s
                i += 1
        # если не найдено нужное (по т. Штурмана) число корней, уменьшаем шаг в 2 раза
        if (i < count):
            i = 0
            step /= 2
        else:
            break
    root_interval[i] = step
    for i in range(count):
        s = root_interval[i]
        print('Интервал: [{:}; {:}] \t  Значение: {:<20} ->   {:<20}'.format(s, s + step, p(s), p(s + step)))
    return root_interval


