import numpy as np
import ExplicitSchema as ES
import ImplicitSchema as IS
import pandas as pd
import pylab


def table(a, b, T, g1, g2, k, f, fi, gy, t_cond, schema_cond):

    ns = [10, 20, 40, 80]#, 160]

    table = np.zeros(shape=(len(ns), 8))
    for i in range(0, len(ns)):

        h = (b - a) / ns[i]
        N = ns[i]

        if (t_cond == 1):
            t = (h*h) / (2*k)
        else:
            t = (h*h) / 6

        M = int(T / t) + 1
        # 1/4 and center of tau coordinate 
        tn1 = int(M / 4)
        tn2 = int(M / 2)
    
        if (schema_cond == 'explicit'):
            M1 = ES.explicit(t, h, a, b, g1, g2, T, k, f, fi, gy, print_res=False)[0]
            M2 = ES.explicit(t, h*2, a, b, g1, g2, T, k, f, fi, gy, print_res=False)[0]
        elif (schema_cond == 'implicit'):
            M1 = IS.implicit(t, h, a, b, g1, g2, T, k, f, fi, gy, print_res=False)[0]
            M2 = IS.implicit(t, h*2, a, b, g1, g2, T, k, f, fi, gy, print_res=False)[0]
        else:
            printf('Wrong schema name')
            exit()
        
        sol1l = M1[tn1]
        sol1c = M2[tn1]
        sol2l = M1[tn2]
        sol2c = M2[tn2]  

        table[i][0] = ns[i]
        table[i][1] = t
        table[i][2] = np.sqrt(sum((sol1c - sol1l[::2]) ** 2)/len(sol1c))
        table[i][3] = np.sqrt(sum((sol2c - sol2l[::2]) ** 2)/len(sol1c))
        table[i][4] = max(abs(sol1c - sol1l[::2]))
        table[i][5] = max(abs(sol2c - sol2l[::2]))
        table[i][6] = tn1*t
        table[i][7] = tn2*t

    print_table(t_cond, gy, schema_cond, table, ns, a, b, k)

    return table



def print_table(t_cond, gy, schema_cond, table, ns, a, b, k):
    SUB = str.maketrans("12", "₁₂")
    df = pd.DataFrame(table, columns=['N', 't', 's(t=t1)'.translate(SUB), 's(t=t2)'.translate(SUB), 
                                      'max|t1|'.translate(SUB), 'max|t2|'.translate(SUB), 't1', 't2'])
    df[:-1]

    if (t_cond == 1):
        formula = 't = (h*h) / (2*k)'
    else:
        formula = 't = (h*h) / 6' 
    print('\n\n{:} schema. GY variant {:}. formula {:}\n'.format(schema_cond, gy, formula))
    print(df)
    
    error = [r[2] for r in table]
    h = [(b - a) / i for i in ns]
    t = [(hi*hi) / (2*k) for hi in h]
    #print(error)
    #print(h)

    figure = pylab.figure()
    ax1 = figure.add_subplot (1, 2, 1)
    pylab.plot (h, error, 'r')
    ax1.set_yscale ('log')
    ax1.set_xlabel('h')
    ax1.set_ylabel('error')

    ax2 = figure.add_subplot (1, 2, 2)
    pylab.plot (t, error)
    ax2.set_yscale ('log')
    ax2.set_xlabel('t')
    ax2.set_ylabel('error')
    pylab.show()