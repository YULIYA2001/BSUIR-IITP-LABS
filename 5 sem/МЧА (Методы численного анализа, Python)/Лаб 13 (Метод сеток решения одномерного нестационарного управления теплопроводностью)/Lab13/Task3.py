import numpy as np
import sympy as sp 
import matplotlib.pyplot as plt
from celluloid import Camera


def findSolution(t, h, a, b, A_, B_, T, k, f, fi):
    N = int((b - a)/h) + 1
    M = int(T / t) + 1

    M_ = np.zeros((M, N))
    X = np.linspace(a, b, N)
    
    M_[0,:] = np.array([fi(i) for i in np.linspace(a, b, N)])
    M_[:,0] = np.array([A_ for i in np.linspace(fi(a), fi(b), M)])
    M_[:,-1] = np.array([B_ for xi in np.linspace(fi(a), fi(b), M)])
    for i in range(1, M):
        for j in range(1, N-1):
            M_[i][j] = k(X[j] + h/2)*M_[i-1][j+1]*t/(h*h) + \
                (1 - (k(X[j] + h/2) + k(X[j] - h/2))*t/(h*h)) * M_[i-1][j] + \
                k(X[j] - h/2)*M_[i-1][j-1]*t/(h*h) + t*f(X[j])*(1 - np.exp(-i*t))

    print('t = {:}, h = {:}, M = {:}, N = {:}'.format(t, h, M, N))
    print('fi = {:}, k = {:}, f = {:}\nX = {:}\nMatrix:\n{:}'.format(
        fi(sp.symbols('x')), k(sp.symbols('x')), f(sp.symbols('x')), X, M_))
    return M_, X


def task3():
    # Вариант 3
    a = 0.5
    b = 1.5
    A_ = 2.0
    B_ = 6.0
    l = b - a

    def k(x):
        return x**(-2)
    def f(x):
       return -2.0 * x**2 - 2.*x 
    def fi(x):
       return (B_ - A_)*(x - 0.5)/l + A_

    T = abs(fi(b)-fi(a))

    
    # Тестовый пример (Вариант 1)
    '''a = 1
    b = 2
    A_ = 3.0
    B_ = 0
    l = b - a
    def k(x):
        return x**(3)
    def f(x):
       return 10 * x**(1/4)
    def fi(x):
       return (B_ - A_)*(x - a)/l + A_
    T = abs(fi(b)-fi(a))
    '''

    print("Задание 3.\nПромоделировать нестационарные процессы теплопроводности в зависимости от" +
         "входных данных задачи − коэффициента теплопроводности и начальной температуры")

    t, h = 0.0005, 0.1
    #t, h = 0.05, 0.01
    
    if fi(b) > fi(a):
        if fi(b)*t/h**2 > 1./2.:
            print('Wrong h or t')
            return
    else:
        if fi(a)*t/h**2 > 1./2.:
            print('Wrong h or t')
            return    

    Matrix, X = findSolution(t, h, a, b, A_, B_, T, k, f, fi)

    plt.plot(X, Matrix[0], label='T = 0t')
    plt.plot(X, Matrix[5], label='T = 5t')
    plt.plot(X, Matrix[20], label='T = 20t')
    plt.plot(X, Matrix[200], label='T = 200t')
    plt.legend(loc='best')
    plt.show()

    # animation
    fig = plt.figure()
    camera = Camera(fig)
    for i in range(0, len(Matrix), 50):  #400 для рисунка в статике (50 для анимации)
        plt.plot(X, Matrix[i], label=i)
        camera.snap()
    animation = camera.animate()
    animation.save('task3.gif', writer = 'imagemagick')
    #animation.save('task3-test.gif', writer = 'imagemagick')
    
    # решение из задания 1
    import Task1
    C = lambda set: 1
    K = lambda x, set: C(set) * k(x)
    Y2 = (Task1.findSolution(1, f, K, C, lambda set: A_, lambda set: B_, a, b, 0))
    X2 = np.linspace(a, b, 100)
    plt.plot(X2, [Y2.subs(sp.symbols('x'), X2[i]) for i in range(len(X2))], 'r:')
    #plt.legend(loc='best')
    plt.show()

    
    Matrix_2, X_2 = findSolution(t, h, a, b, A_, B_, T, k, f, lambda x: 2*(B_ - A_)*(x - a)/l + A_)
    Matrix_3, X_3 = findSolution(t, h, a, b, A_, B_, T, k, f, lambda x: 0.5*(B_ - A_)*(x - a)/l + A_)

    t_ = [100, 300, 500, 1000]
    for i in range(len(t_)):
        plt.plot(X, Matrix[t_[i]], label='fi = (B_ - A_)*(x - a)/l + A_')
        plt.plot(X_2, Matrix_2[t_[i]], label='fi = 2*(B_ - A_)*(x - a)/l + A_')
        plt.plot(X_3, Matrix_3[t_[i]], label='fi = 0.5*(B_ - A_)*(x - a)/l + A_')
        plt.title('T = {:}t'.format(t_[i]))
        plt.legend(loc='best')
        plt.show()