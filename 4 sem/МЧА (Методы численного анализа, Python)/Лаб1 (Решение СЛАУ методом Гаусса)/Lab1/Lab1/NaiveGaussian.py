import numpy as np

# Метод Гаусса (схема единственного деления)
def Naive_Gaussian_Elimination_Method(arr):
    A = arr.copy()
    n = len(A)
    stop = False
    # прямой ход алгоритма
    for k in range (n - 1):
        for i in range(n - k - 1):
            if A[k][k] == 0:
                stop = True
                print("Ноль на главной диагонали. Вычисления множителей и обратная подстановка требуют " +
                "деления на главные элементы akk(k-1). Поэтому если один из главных элементов равен" +
                " нулю, то схема НЕ МОЖЕТ БЫТЬ реализована.")
                break
            q = A[i + 1 + k][k] / A[k][k]
            for j in range(len(A[i])):
                A[i + k + 1][j] = float(A[i + k + 1][j]) - float(A[k][j]) * q
        if stop == True:
            break

    if stop != True:
        print("Верхнетреугольная матрица A:")
        print(A)
        # обратный ход алгоритма
        x = np.zeros((n))
        for k in range(n):
            d = 0
            for j in range(k):
                s = A[n - k - 1][n - k + j] * x[n - k + j]
                d += s
            x[n - k - 1] = (A[n - k - 1][n] - d) / A[n - k - 1][n - k - 1]

        print("Вектор решений x:")
        for i in range(len(x)):
            x[i] = round(x[i] * 10 ** 4) / 10 ** 4
            print("x[" + str(i+1) + "] = " + str(x[i]))
