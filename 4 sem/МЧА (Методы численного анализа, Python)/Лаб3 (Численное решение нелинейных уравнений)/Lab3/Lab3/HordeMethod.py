def Horde_Method(f, a, b, eps):
    # условия сходимости метода хорд
    if (f(a) * f.deriv(2)(a) > 0):
        print("Условие сходимости выполнено.")
        k = a
        prevx = b
    elif (f(b) * f.deriv(2)(b) > 0):
        print("Условие сходимости выполнено.")
        k = b
        prevx = a
    else:
        print("Smth wrong... Too large interval.")
        return

    print('Итерация {:}: \t x0 = {:<20} \t f(x) = {:<20}'.format(1, prevx, f(prevx)))
    iter = 2
    while (True):        
        if (f(k) - f(prevx) == 0):
            print("В методе деление на 0.")
            return
        x = prevx - f(prevx) / (f(k) - f(prevx)) * (k - prevx)     
        print('Итерация {:}: \t x = {:<20} \t f(x) = {:<20}'.format(iter, x, f(x)))
        #if (abs(f(x)) < eps):
        if (abs(prevx - x) < eps):
            print('\nРешение x =', x, ' найдено с точностью е =', eps, 'на', iter, 'итерации.\n')
            break
        prevx = x
        iter += 1
        if (iter > 1000):
            print("Let's stop! Too mach iterations")
            break

