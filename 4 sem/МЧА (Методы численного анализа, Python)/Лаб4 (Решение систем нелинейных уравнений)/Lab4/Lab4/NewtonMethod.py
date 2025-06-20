import numpy as np

def Newton_Method(x0, y0, eps):
    iteration = 0
    (x, y) = (x0, y0)
    while True:
        iteration += 1
        print("{:} итерация:\tx = {:<25} y = {:<25}".format(iteration, x, y))
        j = J(x, y)
        f = np.array([[expr1(x, y)], [expr2(x, y)]])
        D = np.linalg.solve(j, -f)
        x += D[0][0]
        y += D[1][0]
        if (not (np.isfinite(x) and np.isfinite(y))):
            print("Ряд приближений расходится")
            return
        if (iteration > 10000):
            print("\nПлохо выбрано начальное приближение\n")
            return
        if (max(abs(D)) < eps):
            break
    print("\nРешение (x, y) = ({:.4f}, {:.4f}) найдено с точностью е = {:} на {:} итерации.\n"
          .format(x, y, eps, iteration))

# Уравнения
def expr1(x, y):
    return np.tan(x * y + 0.2) - x
def expr2(x, y):
    return 0.9 * x ** 2 + 2 * y ** 2 - 1

# Матрица Якоби системы
def J(x, y):
    return np.array([[y * (1 + np.tan(x * y + 0.2) ** 2) - 1, x * (1 + np.tan(x * y + 0.2) ** 2)],
                        [1.8 * x, 4 * y]])


'''
################### Test #####################
def expr1(x, y):
    return x + 2 * y - 2
def expr2(x, y):
    return x ** 2 + 2 * y ** 2 - 2
def J(x, y):
    return np.array([[1, 2], [2 * x, 4 * y]])
##############################################
'''