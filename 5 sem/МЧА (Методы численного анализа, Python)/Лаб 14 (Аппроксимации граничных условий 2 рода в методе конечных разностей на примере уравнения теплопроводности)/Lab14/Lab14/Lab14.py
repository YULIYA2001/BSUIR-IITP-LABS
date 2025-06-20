import ExplicitSchema as ES
import ImplicitSchema as IS
import PrintTable as PT
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

var = 3
print("ЛР 14. Аппроксимации граничных условий второго рода в методе конечных разностей на примере" +
      " уравнения теплопроводности.\n")
print("\t\t\tВариант {0}".format(var))
print("-" * 50)


# Вариант 3
a = 0
b = 1
g1 = lambda t: 5*t
g2 = lambda t: 5*t
T = 0.5
k = 0.1
def f(x, t):
    return 0
def fi(x):
    return x*(1 - x)


n = 10
h = (b - a) / n
t_cond = 1
if (t_cond == 1):
    t = (h*h) / (2*k)
else:
    t = (h*h) / 6

# step of grafic
num = 2

e11 = PT.table(a, b, T, g1, g2, k, f, fi, gy=1, t_cond=1, schema_cond='explicit')
i1 = PT.table(a, b, T, g1, g2, k, f, fi, gy=1, t_cond=1, schema_cond='implicit')
e12 = PT.table(a, b, T, g1, g2, k, f, fi, gy=1, t_cond=2, schema_cond='explicit')
e21 = PT.table(a, b, T, g1, g2, k, f, fi, gy=2, t_cond=1, schema_cond='explicit')
i2 = PT.table(a, b, T, g1, g2, k, f, fi, gy=2, t_cond=1, schema_cond='implicit')
e22 = PT.table(a, b, T, g1, g2, k, f, fi, gy=2, t_cond=2, schema_cond='explicit')

# table for comparison
tab = np.zeros(shape=(4, 6))
tab[:,0] = [r[2] for r in e11]
tab[:,1] = [r[2] for r in i1]
tab[:,2] = [r[2] for r in e12]
tab[:,3] = [r[2] for r in e21]
tab[:,4] = [r[2] for r in i2]
tab[:,5] = [r[2] for r in e22]
df = pd.DataFrame(tab, columns=['e11', 'i1', 'e12', 'e21', 'i2', 'e22'])
df[:-1]
print(df)

Matrix, X = ES.explicit(t, h, a, b, g1, g2, T, k, f, fi, 1, print_res=True)
for i in range(0, len(Matrix), num):
    plt.plot(X, Matrix[i], label='{:}t'.format(i))
plt.legend(loc='best')
plt.title('Явная схема, 1 способ. h = {:.4f}'.format(h))
plt.show()

Matrix, X = IS.implicit(t, h, a, b, g1, g2, T, k, f, fi, 1, print_res=True)
for i in range(0, len(Matrix), num):
    plt.plot(X, Matrix[i], label='{:}t'.format(i))
plt.legend(loc='best')
plt.title('Неявная схема, 1 способ. h = {:.4f}'.format(h))
plt.show()

Matrix, X = ES.explicit(t, h, a, b, g1, g2, T, k, f, fi, 2, print_res=True)
for i in range(0, len(Matrix), num):
    plt.plot(X, Matrix[i], label='{:}t'.format(i))
plt.legend(loc='best')
plt.title('Явная схема, 2 способ. h = {:.4f}'.format(h))
plt.show()

Matrix, X = IS.implicit(t, h, a, b, g1, g2, T, k, f, fi, 2, print_res=True)
for i in range(0, len(Matrix), num):
    plt.plot(X, Matrix[i], label='{:}t'.format(i))
plt.legend(loc='best')
plt.title('Неявная схема, 2 способ. h = {:.4f}'.format(h))
plt.show()
  