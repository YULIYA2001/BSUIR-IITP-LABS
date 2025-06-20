import numpy as np

# метод прогонки
def sweep_method(A, d, n):
    # коэффициенты трехдиагональной матрицы
    b = np.zeros(n)
    for i in range(n):
        b[i] = A[i][i]

    a = np.zeros(n)
    for i in range(n-1):
        a[i] = A[i+1][i]
    a[n-1] = 0

    c = np.zeros(n)
    for i in range(n-1):
        c[i] = A[i][i+1]
    c[n-1] = 0

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

    x = np.zeros(n)
    x[n-1] = beta[n-1]
    for i in range(n-2, -1, -1):
        x[i] = alpha[i]*x[i+1] + beta[i]

    return x
