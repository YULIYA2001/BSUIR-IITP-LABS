def Half_Division_Method(f, left, right, eps):
    a = left
    b = right
    # условия сходимости метода половинного деления
    if (f(a) * f(b) < 0):
        print("Условие сходимости выполнено.")
    else:
        print("Условие сходимости не выполнено.")
        return
    iter = 1
    x = 0               # значение для prevx (по умолчанию)
    while (True):
        prevx = x
        x = (a + b) / 2.0
        print('Итерация {:}: \t x = {:<20} \t f(x) = {:<20}'.format(iter, x, f(x)))
        #if (abs(f(x)) < eps):
        if (abs(prevx - x) < eps):
            print('\nРешение x =', x, ' найдено с точностью е =', eps, 'на', iter, 'итерации.\n')
            break
        iter += 1
        if (f(a) * f(x) < 0):
            b = x
        else:
            a = x