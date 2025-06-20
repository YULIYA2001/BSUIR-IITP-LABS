def Newton_Method(f, l, r, eps):
    Df = f.deriv(1)

    # дополнительная попытка избежать f'(x0) = 0
    if(Df(l) == 0):
        l -= 0.1
    if(Df(r) == 0):
        r += 0.1
    x = l          # по умолчанию
    # достаточные условия сходимости метода Ньютона
    if(Df(l) == 0 or Df(r) == 0):
        print("Деление на 0 при проверке условий сходимости.")
        return
    else:
        if(abs(f(l) / Df(l)) < r - l and abs(f(r) / Df(r)) < r - l):
            print("- Для отрезка [", l, "; ", r, "] выполняются условия сходимости.")
        else:
            print("Для отрезка [", l, "; ", r, "] НЕ выполняются условия сходимости.") 
            print("f(l) / f'(l)", f(l) / Df(l), "f(r) / f'(r)", f(r) / Df(r), "r - l", r - l)

    if(f(l) * Df.deriv(1)(l) > 0):
        print("- Условие сходимости для левой границы выполнено. x0 =", l, "(левая граница)")
        x = l
    elif(f(r) * Df.deriv(1)(r) > 0):
        print("- Условие сходимости для правой границы выполнено. x0 =", r, "(правая граница)")
        x = r
    print()

    iter = 1
    while (True):
        prevx = x        
        fx = f(x)
        print('Итерация {:}: \t x = {:<20} \t f(x) = {:<20}'.format(iter, x, fx))
        Dfx = Df(x)
        if Dfx == 0:
            print("Деление на 0. Первая производная f'(", x, ") = 0")
            return
        x = x - fx / Dfx
        iter += 1
        #if (abs(f(x)) < eps):
        if (abs(prevx - x) < eps):
            print('Итерация {:}: \t x = {:<20} \t f(x) = {:<20}'.format(iter, x, f(x)))
            print('\nРешение x =', x, ' найдено с точностью е =', eps, 'на', iter, 'итерации.\n')
            break
    
