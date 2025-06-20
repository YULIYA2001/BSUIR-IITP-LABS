
def print_matrix(M):

    for i in range(len(M)):
        for j in range(len(M[i])):
            print('{:.4f}'.format(M[i][j]), end='   ')
        print()
