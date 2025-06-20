import numpy as np

def Method_Jacobi(A, eps):
    n = len(A)

    Vect = np.eye(n)
    iter = 1
    s = 0               # для достижения условия выхода из цикла
    while True:
        max_i = 0
        max_j = 1
        for i in range(n):
            for j in range(i + 1, n):
                if (abs(A[i][j]) > abs(A[max_i][max_j])):
                    max_i = i
                    max_j = j

        V = np.eye(n)
        if (A[max_i][max_i] == A[max_j][max_j]):
            p = np.pi / 4
        else:
            p = 2 * A[max_i][max_j] / (A[max_i][max_i] - A[max_j][max_j])
        cos = np.cos(1 / 2 * np.arctan(p))
        sin = np.sin(1 / 2 * np.arctan(p))
        V[max_i][max_i] = cos
        V[max_i][max_j] = -sin
        V[max_j][max_i] = sin
        V[max_j][max_j] = cos
        print("\n", iter, " итерация:\n---------------------\nV(", iter - 1, ") = \n", V, "\n")
        #A = V.transpose() * A * V
        A = V.transpose().dot(A.dot(V))
        np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")
        print("А(", iter, ") = \n", A, "\n")
        # Vect = Vect * V
        Vect = Vect.dot(V)
        # выход из цикла, когда сумма квадратов диагональных элементов |s - prevs| < eps
        prevs = s
        s = 0
        for i in range(n):
            for j in range(n):
                if (i != j):    
                    s += A[i][j] * A[i][j]
        if (abs(s - prevs) < eps):
            break
        iter +=1

    print("\n\t  Ответ:\n\t~~~~~~~~~\n")
    print("Количество итераций: ", iter)
    print("\nСобственные значения:")
    eigenvalues = np.diag(A)
    print(eigenvalues)

    print("\nСобственные векторы: ")
    # вывод 4 цифр после запятой
    np.set_printoptions(suppress = True, precision = 4, floatmode = "fixed")
    Vec = Vect.transpose()
    for i in range(n):
        print("V(", i + 1, "): ", Vec[i], "^T")
    #print(Vect)

    # проверка ортогональности собственных векторов
    print("\nПроверка ортогональности собственных векторов:")
    lenv = len(Vec)
    for i in range(lenv):
        for j in range(i+1, lenv):
            print("Vec(", i, ") * Vec(", j, ") = %0.4f" % np.dot(Vec[i], Vec[j]))
            if(round(np.dot(Vec[i], Vec[j]), 4) != 0):
                print("Упс! Что-то не так. Векторы не ортогональны");
                return;
    print("Все отлично! Векторы ортогональны\n");
