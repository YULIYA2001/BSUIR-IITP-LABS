# ПОГРЕШНОСТЬ по формуле ПОГРЕШНОСТЬ < ||(F-Y) / L(F-Y)||, где ||X||=int((X)**2 / (b - a), от а до b) ^ 1/2

import numpy as np
import sympy as sp 

from scipy.integrate import quad


def error(F, LF, left, right):
    
    def integrand1(x_):
        x = sp.symbols('x')
        try:
            F_ = F.subs([(x, x_)])
        except:
            F_ = F
        return (F_)**2

    def integrand2(x_):
        x = sp.symbols('x')
        try:
            LF_ = LF.subs([(x, x_)])
        except:
            LF_ = LF
        return (LF_)**2

    E = (quad(integrand1, left, right)[0] / (right - left)) / (quad(integrand2, left, right)[0] / (right - left))

    return np.sqrt(E)
