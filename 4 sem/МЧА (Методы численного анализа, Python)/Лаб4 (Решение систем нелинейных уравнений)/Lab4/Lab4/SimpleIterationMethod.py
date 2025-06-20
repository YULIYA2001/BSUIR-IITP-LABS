import numpy as np

def Simple_Iteration_Method(x0, y0, eps):
    iteration = 1
    (x, y) = (x0, y0)
    print("{:} итерация:\tx = {:<25} y = {:<25}".format(iteration, x, y))
    while True:
        iteration += 1
        prevx = x
        prevy = y
        x = Xfrom1(x, y)
        y = Yfrom2(x, y)
        print("{:} итерация:\tx = {:<25} y = {:<25}".format(iteration, x, y))
        if (not (np.isfinite(x) and np.isfinite(y))):
            print("Ряд приближений расходится")
            return
        if (iteration > 10000):
            print("\nПлохо выбрано начальное приближение\n")
            return
        if (max(abs(x - prevx), abs(y - prevy)) < eps):
            break
    print("\nРешение (x, y) = ({:.4f}, {:.4f}) найдено с точностью е = {:} на {:} итерации.\n"
          .format(x, y, eps, iteration))


# Х выражается из первого уравнения x = f(x,y)
def Xfrom1(x, y):
    return np.tan(x * y + 0.2)

# Y выражается из второго уравнения y = f(x,y)
def Yfrom2(x, y):
    return np.sqrt((1 - 0.9 * x ** 2) / 2)

'''
################# Test #####################
def Xfrom1(x, y):
    return  - 2 * y + 2
def Yfrom2(x, y):
    return np.sqrt((2 - x ** 2) / 2)
############################################
'''