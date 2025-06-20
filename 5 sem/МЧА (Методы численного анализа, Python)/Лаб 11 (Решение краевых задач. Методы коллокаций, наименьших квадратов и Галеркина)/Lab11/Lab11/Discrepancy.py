# НЕВЯЗКА по формуле: int((y - F)**2 / (b - a), от а до b) ^ 1/2

import numpy as np
import sympy as sp 

from scipy.integrate import quad

def discrepancy(my_F,  F, left, right, P, Q):

    def integrand(x_):
        x = sp.symbols('x')
        try:
            F_ = F.subs([(x, x_)])
        except:
            F_ = F
        try:
            my_F_ = my_F.subs([(x, x_)])
        except:
            my_F_ = my_F

        return (F_ - my_F_)**2

    D = quad(integrand, left, right)[0]
    return np.sqrt(D / (right - left))
