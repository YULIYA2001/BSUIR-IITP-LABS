import numpy as np
import SimpleIteration as SI
import SeidelMethod as SM
import SufficientConditions as SC
from numpy import linalg as LA

# Функция перестановки строк местами
def swap_rows(arr, frm, to):
    arr[[frm, to],:] = arr[[to, frm],:]

# Тестовые примеры
#A = np.array([[2, 1], 
#              [1, -2]], dtype = float)
#b = np.array([[3], [1]], dtype = float)

#A = np.array([[10, 1, -1], 
#              [1, 10, -1], 
#              [-1, 1, 10]], dtype = float)
#b = np.array([[11], [10], [10]], dtype = float)

C = np.array([[0.01, 0, -0.02, 0, 0],
              [0.01, 0.01, -0.02, 0, 0], 
              [0, 0.01, 0.01, 0, -0.02], 
              [0, 0, 0.01, 0.01, 0], 
              [0, 0, 0, 0.01, 0.01]])
D = np.array([[1.33, 0.21, 0.17, 0.12, -0.13], 
              [-0.13, -1.33, 0.11, 0.17, 0.12], 
              [0.12, -0.13, -1.33, 0.11, 0.17], 
              [0.17, 0.12, -0.13, -1.33, 0.11], 
              [0.11, 0.67, 0.12, -0.13, -1.33]])
k = 5
b = np.array([[1.2], [2.2], [4.0], [0.0], [-1.2]])
A = k * C + D
eps = 0.0001

# перестановка строк, если 0 на главной диагонали
for i in range(len(A)):
    j = 4
    while(A[i][i] == 0):
        swap_rows(A, i, j)
        j -= 1

# проверка достаточных условий сходимости последовательности простых итераций
if (SC.Sufficient_Conditions(A) == 0):
    a = np.hstack((A, b))
    print("\n                                    Вариант 5                                   ")
    print("----------------------------------------------------------------------------------")
    print("Расширенная матрица A:")
    print(a)
    print("1. Метод простых итераций:")
    SI.Simple_Iteration_Method(A, b, eps)
    print("----------------------------------------------------------------------------------")
    print("2. Метод Зейделя:")
    SM.Seidel_Method(A, b, eps)
