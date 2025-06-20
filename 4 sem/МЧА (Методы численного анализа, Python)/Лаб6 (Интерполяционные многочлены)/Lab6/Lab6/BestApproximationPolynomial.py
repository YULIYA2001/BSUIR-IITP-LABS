import numpy as np

def LeastSquareMethod(xi, yi, x, p):
    ''' Вычисление многочлена наилучшего приближения порядка m в точке х '''
    c = np.zeros(2*p + 1)
    b = np.zeros(p + 1)
    for j in range(len(c)):
        for i in range(len(xi)):
            c[j] = c[j] + xi[i]**j
    for j in range(len(b)):
        for i in range(len(xi)):
            b[j] = b[j] + yi[i] * xi[i]**j
    M = []
    for i in range(p + 1):
        M.append([])
        for j in range(p + 1):
            M[i].append(c[j + i])
    P = np.linalg.solve(M, b)

    lenres = len(P)
    y = 0

    for i in range(lenres):
        y = y + P[i] * x**i

    # Погрешность приближения многочленом по методу наименьших квадратов
    sum = 0
    for i in range(len(yi)):
        sumP = 0
        for j in range(len(P)):
            sumP = sumP + P[j] * xi[i]**j
        sum = sum + (yi[i] - sumP)**2
    D = np.sqrt(sum/(len(yi) + 1))
    #print("Погрешность приближения многочленом порядка", p, "по методу наименьших квадратов: D =", D)

    result = [y, D]
    return result
'''
K=11
a = np.zeros(K)
for k in range(K+1):
    for i in range(k+1, K+1):
	   M = sums[i][k] / sums[k][k];
	   for j in range(k, K+1):
	       sums[i][j] -= M * sums[k][j]
	   b[i] -= M*b[k];
    
   for i in range((K+1)-1, -1, -1):
       s = 0;
       for j in range(i,K+1):
	        s = s + sums[i][j]*a[j];
       a[i] = (b[i] - s) / sums[i][i];
'''