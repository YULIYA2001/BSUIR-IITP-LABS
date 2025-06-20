# аппроксимация производных по формулам: diff(y0)=(-y2+4*y1-3*y0)/2*h  diff(yn)=(3*y(n)-4*y(n-1)+y(n-2))/2*h
import numpy as np

# метод прогонки
def sweep_method(p, q, f_, h, n, X, al_1, be_1, al_2, be_2, A, B):
    '''метод прогонки для дифф. уравнения 2 порядка с обобщенными граничными условиями
    p, q, f_, - функции от х в условии дифф уравнения
    h, n, X, - шаг, кол-во разбиений отрезка, массив точек разбиения
    al_1, be_1, al_2, be_2, - функции из обобщенных граничных условий, 
    A, B - числа из обобщенных граничных условий'''

    # коэффициенты трехдиагональной матрицы
    a = np.zeros(n-1)
    b = np.zeros(n-1)
    c = np.zeros(n-1)
    d = np.zeros(n-1)

    for i in range(n-1):
        a[i] = 2 - p(X[i+1])*h
        b[i] = 2*h*h*q(X[i+1]) - 4
        c[i] = 2 + p(X[i+1])*h
        d[i] = 2 * h * h * f_(X[i+1])
    # подстановка у0 и уn из обобщенных граничных условий
    b[0] += -4*a[0]*be_1 / (2*h*al_1 - 3*be_1)
    c[0] += a[0]*be_1 / (2*h*al_1 - 3*be_1) 
    d[0] += -2*a[0]*h*A / (2*h*al_1 - 3*be_1) 
    a[-1] += -c[-1]*be_2 / (2*h*al_2 + 3*be_2) 
    b[-1] += 4*c[-1]*be_2 / (2*h*al_2 + 3*be_2)
    d[-1] += -2*c[-1]*h*B / (2*h*al_2 + 3*be_2) 

    # сам метод прогонки
    n = n-1
    alpha = np.zeros(n)
    beta = np.zeros(n)

    y = np.zeros(n)
    y[0] = b[0]
    alpha[0] = -c[0] / y[0]
    beta[0] = d[0] / y[0]
    for i in range(1, n-1):
        y[i] = b[i] + a[i]*alpha[i-1]
        alpha[i] = -c[i] / y[i]
        beta[i] = (d[i] - a[i]*beta[i-1]) / y[i]
    y[n-1] = b[n-1] + a[n-1]*alpha[n-2]
    beta[n-1] = (d[n-1] - a[n-1]*beta[n-2]) / y[n-1]
    # обратный ход метода прогонки
    x = np.zeros(n)
    x[n-1] = beta[n-1]
    for i in range(n-2, -1, -1):
        x[i] = alpha[i]*x[i+1] + beta[i]

    # нахождение y0 и yn из обобщенных граничных условий
    x = np.insert(x, 0, (2*h*A + be_1*x[1] - 4*be_1*x[0]) / (2*h*al_1 - 3*be_1))
    x = list(x)
    x.append((2*h*B + 4*be_2*x[-1] - be_2*x[-2]) / (2*h*al_2 + 3*be_2))
    return x
