def derivative(f, x, method='central', h=0.0000001):
    '''Compute the difference formula for f'(x) with step size h.'''
    if method == 'central':
        return (f(x + h) - f(x - h))/(2*h)
    elif method == 'forward':
        return (f(x + h) - f(x))/h
    elif method == 'backward':
        return (f(x) - f(x - h))/h
    else:
        raise("Smth wrong!")

#print("По формуле      y' =    (y(k) - y(k-1)) / h    =", derivative(func, x, 'backward'))

def derivative_2(f, x, h=0.0000001):
    '''Compute the difference formula for f''(x) with step size h.'''
    return (f(x + h) - 2*f(x) + f(x - h))/(h*h)
