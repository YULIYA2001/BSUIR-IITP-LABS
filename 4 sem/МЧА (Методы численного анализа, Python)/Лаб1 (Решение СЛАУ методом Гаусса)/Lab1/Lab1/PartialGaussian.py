import numpy as np

# Функция перестановки строк местами
def swap_rows(arr, frm, to):
    arr[[frm, to],:] = arr[[to, frm],:]

# Метод Гаусса с выбором главного элемента по столбцу (схема частичного выбора)
def Gaussian_Elimination_with_Partial_Pivoting(arr):
    A = arr.copy()
    n = len(A)
    stop = False
    # прямой ход алгоритма
    for k in range (n - 1):
        for s in range(n - k - 1):                      # поиск максимального           
            if abs(A[k][k]) < abs(A[s + k + 1][k]):     # элемента в столбце
                swap_rows(A, k, s + k + 1)              # на каждом шаге
        for i in range(n - k - 1):
            if A[k][k] == 0:
                stop = True
                print("Ноль на главной диагонали")
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
