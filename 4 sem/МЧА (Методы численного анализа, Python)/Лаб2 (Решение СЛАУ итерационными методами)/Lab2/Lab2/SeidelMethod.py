import numpy as np

def Seidel_Method(A, b, eps):
    n = len(A)
    prevX = np.zeros(n)

    # выбор начального значения
    #for i in range(n):
    #    prevX[i] = b[i] / A[i][i] 

    # вывод 0 итерации
    print("выбрано начальное значение: ")
    print(prevX)
    count = 1

    X = np.zeros(n)
    
    while(True):
        for i in range(n):
            if (A[i][i] == 0):
                print("Ноль на главной диагонали. Деление на 0")
                return
            X[i] = b[i]
            for j in range(n):
                if (j < i):
                    X[i] -= A[i][j] * X[j]
                if (j > i):
                    X[i] -= A[i][j] * prevX[j]
            X[i] /= A[i][i]

        # вывод каждой итерации
        print(str(count) + " итерация: ")
        count += 1
        print(X)

        flag = True
        for i in range(n - 1): 
            if (abs(X[i] - prevX[i]) > eps):
                flag = False
                break
            else:
                print("Точность для x[" + str(i + 1) + "]: " + str(abs(X[i] - prevX[i])) + " < " + str(eps))

        for i in range(n):
            prevX[i] = X[i]

        if (flag == True):
            # для расчета невязки
            s = np.zeros((n))
            print("Вектор решений x:")
            for i in range(len(X)):
                X[i] = round(X[i] * 10 ** 4) / 10 ** 4
                print("x[" + str(i + 1) + "] = " + str(X[i]))
                # расчет невязки
                for j in range(n - 1):
                    s[i] += A[i][j] * X[j]
                s[i] = abs(b[i] - s[i])
            print("Невязка: ")
            print(s)
            break
