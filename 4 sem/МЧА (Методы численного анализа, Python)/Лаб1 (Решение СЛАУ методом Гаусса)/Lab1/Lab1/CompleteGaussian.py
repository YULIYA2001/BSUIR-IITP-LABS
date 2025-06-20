import numpy as np

# Функция перестановки строк местами
def swap_rows(arr, frm, to):
    arr[[frm, to],:] = arr[[to, frm],:]
# Функция перестановки столбцов местами
def swap_cols(arr, frm, to):
    arr[:,[frm, to]] = arr[:,[to, frm]]

# Метод Гаусса с выбором главного элемента по матрице (схема полного выбора)
def Gaussian_Elimination_with_Complete_Pivoting(arr):
    A = arr.copy()
    n = len(A)
    stop = False
    E = np.eye(n)

    # прямой ход алгоритма
    for k in range (n - 1):
        max = A[k][k]
        i_max = k
        j_max = k
        # поиск максимального элемента матрицы(подматрицы) и перемещение его на место ведущего
        for s in range(n - k):
            for t in range(n - k):
                if abs(A[s + k][t + k]) > abs(max):
                    max = A[s + k][t + k]
                    i_max = s + k
                    j_max = t + k
        swap_rows(A, i_max, k)
        swap_cols(A, j_max, k)
        swap_cols(E, j_max, k)      # "запомнить" перемещение столбцов в вспомагательной диагональной матрице

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

        x = E.dot(x)        # перестановка корней в правильном порядке (согласно вспомогательной матрице)
        print("Вектор решений x:")
        for i in range(len(x)):
            x[i] = round(x[i] * 10 ** 4) / 10 ** 4
            print("x[" + str(i+1) + "] = " + str(x[i]))
        # расчет невязки
        A = arr.copy()
        s = np.zeros((n))
        for i in range(len(x)):
            for j in range(n):
                s[i] += A[i][j] * x[j]
            s[i] = abs(A[i][j + 1] - s[i])
        print("----------------------------------------------------------------------------------")
        print("Невязка: ")
        print(s)
