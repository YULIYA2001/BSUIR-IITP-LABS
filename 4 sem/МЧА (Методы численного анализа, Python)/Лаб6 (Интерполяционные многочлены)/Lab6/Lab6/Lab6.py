import numpy as np
import matplotlib.pyplot as plt

import LagrangeNewton as LN
import BestApproximationPolynomial as BAP

k = 5
m = 2.5
xi = np.array([0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])#, 1.5])
pi = np.array([0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01])#, 3.5])
yi = pi + (-1)**k * m
point = 0.47
# порядок многочлена для метода наименьших квадратов (многочлен наилучшего приближения)
p = 10

print("\t\t\tВариант 5")
print("x = ", xi)
print("y = ", yi)

if len(xi) != len(yi):
    print("Неверное условие")
    exit()

print("\n\tЗначение многочленов в точке ", point)
print("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
print("\nИнтерполяционного Лагранжа: y = %.14f" % LN.Lagrange(xi, yi, point))
print("Интерполяционного Ньютона: y = %.14f" % LN.Newton(xi, yi, point)[0])
print("Погрешность приближения интерполяционным многочленом: D =", LN.Newton(xi, yi, point)[1])
print("\nНаилучшего приближения: y = %.14f" % BAP.LeastSquareMethod(xi, yi, point, p)[0])    
print("Погрешность приближения многочленом порядка", p, "по методу наименьших квадратов: D =", 
      BAP.LeastSquareMethod(xi, yi, point, p)[1])

# Графики
# массив из 100 элементов, значения которых равномерно распределенны внутри интервала
xinew = np.linspace(np.min(xi), np.max(xi), 100)	
yiL = [LN.Lagrange(xi, yi, i) for i in xinew]
yiN = [LN.Newton(xi, yi, i)[0] for i in xinew]
yiBA = [BAP.LeastSquareMethod(xi, yi, i, p)[0] for i in xinew]
plt.figure(figsize = (10, 7))
#subplot 1
plt.subplot(221)
plt.plot(xi, yi, 'ro', xinew, yiL, color="black")
plt.title(r'Lagrange')
plt.grid(True)
#subplot 2
plt.subplot(222)
plt.plot(xi, yi, 'go', xinew, yiN, color="blue")
plt.title(r'Newton')
plt.grid(True)
#subplot 3
plt.subplot(223)
plt.plot(xi, yi, 'bo', xinew, yiBA, color="yellow")
plt.title(r'BestApproximation')
plt.grid(True)

pol = np.poly1d(np.polyfit(xi, yi, p))
#subplot 4
plt.subplot(224)
plt.plot(xi, yi, 'o', xinew, pol(xinew))
plt.title(r'BestApproximation2')
plt.grid(True)

plt.show()

print(pol(point))

plt.plot(xi, yi, '.')
plt.plot(xinew, yiL, '-', color ='blue')
plt.plot(xinew, yiN, '--', color = 'red')
plt.plot(xinew, yiBA, '-', color = 'yellow')
plt.plot(xinew, pol(xinew), ':', color = 'green')

plt.show()

