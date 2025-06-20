import numpy as np

def Lagrange(xi, yi, x):
	''' Вычисление интерполяционного многочлена Лагранжа в точке х '''
	L = 0.0
	for i in range(len(xi)):
		l = 1.0
		for j in range(len(xi)):
			if (j != i):
				l = l * (x-xi[j]) / (xi[i]-xi[j])
		L = L + l*yi[i]
	return L


#prevL = prevL-L

def divided_diff(xi, yi):
    '''функция для вычисления таблицы разделенных разностей coef (->coefficient)'''
    n = len(yi)
    coef = np.zeros([n, n])
    # первая колонка у-ки
    coef[:,0] = yi
    # остальные колонки по формуле
    for j in range(1, n):
        for i in range(n-j):
            coef[i][j] = (coef[i+1][j-1] - coef[i][j-1]) / (xi[i+j]-xi[i])

    max = coef[0][3]
    for i in range(1, n):
        if max < abs(coef[i][3]):
            max = abs(coef[i][3])

	# возвращает одномерный массив [y0, f(x1,x0), f(x2,x1,x0), ..., f(xn,xn-1,...,x1,x0)]
    result = [coef[0,:], max]
    return result

'''
	# предположим, что функция 3 РАЗА ДИФФРЕРЕНЦИРУЕМА
    n = 4
    c = np.zeros([n, n])
    for i in range(0, n):		# точки y вокруг 0,47
        c[i][0] = yi[i + 3]
    for j in range(1, n):
        for i in range(n-j):
            c[i][j] = (c[i+1][j-1] - c[i][j-1]) / (xi[i+j]-xi[i])
    max = c[0][3]
    for i in range(1, n):
        if max < abs(c[i][3]):
            max = c[i][3]
'''
    

def w(x, xi):
	''' Нужно для подсчета погрешности '''
	res = 1
	for i in range(3, 7):		#4 точки вблизи 0,47
		res = res * (x - xi[i])
	return res
		
def Newton(xi, yi, x):
	''' Вычисление интерполяционного многочлена Ньютона в точке х '''
	coef = divided_diff(xi, yi)[0]

	# Погрешность приближения интерполяционным многочленом в точке х
	max = divided_diff(xi, yi)[1]
	D = max / np.math.factorial(2 + 1) * abs(w(x, xi))

	lenx = len(xi)
	N = coef[lenx - 1]
	for k in range(1, lenx):
		N = coef[lenx-k-1] + (x - xi[lenx-k-1])*N

	result = [N, D]
	return result

'''
N = coef[lenx - 1]
	for k in range(1, lenx):
		N = coef[lenx-k-1] + (x - xi[lenx-k-1])*N

	result = [N, D]
	return result
'''
    
#a = 0.00023322176330997646