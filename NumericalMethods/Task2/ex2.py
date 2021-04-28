import numpy as np

#
#   Created by Oleg Semenov on 7.11.2020
#   This is a simple program for solving symmetric circulant tridiagonal system of linear equations using
#   Thomas algorithm with an addition of Sherman-Morrison algorithm
#

matrix = np.array([[4, 1, 0, 0, 0, 0, 1],
                   [1, 4, 1, 0, 0, 0, 0],
                   [0, 1, 4, 1, 0, 0, 0],
                   [0, 0, 1, 4, 1, 0, 0],
                   [0, 0, 0, 1, 4, 1, 0],
                   [0, 0, 0, 0, 1, 4, 1],
                   [1, 0, 0, 0, 0, 1, 4]])

d = [1, 2, 3, 4, 5, 6, 7]


# beta values for Thomas algorithm
def beta(mat):
    arr = [-mat[0][1] / mat[0][0]]
    for i in range(1, len(mat) - 1):
        arr.append(-mat[i][i + 1] / (mat[i][i - 1] * arr[i - 1] + mat[i][i]))
    arr.append(0)
    return arr


# gamma values for Thomas algorithm
def gamma(mat, b, sol):
    arr = [sol[0] / mat[0][0]]
    for i in range(1, len(mat)):
        arr.append((sol[i] - (mat[i][i - 1] * arr[i - 1])) / ((mat[i][i - 1] * b[i - 1]) + mat[i][i]))
    return arr


def show_matrix(mat, sol):
    arr = []
    for i in range(len(mat)):
        arr.append("|  {}| |  {}  | |  {}  |{}".format((''.join([str(num) + "  " for num in mat[i]])), 'x' + str(i + 1),
                                                       sol[i], '' if (i + 1) % len(mat) else '\n' * 2))
    return '\n'.join(arr)


# thomas algorithm for solving tridiagonal matrices
# the arguments are matrix and the solutions of
def thomas(mat, sol):
    b = beta(mat)
    g = gamma(mat, b, sol)
    x = [g[-1]]
    arr = []
    for i in range(2, len(mat) + 1):
        x.append((b[len(mat) - i] * x[i - 2]) + g[len(mat) - i])
    for i in range(len(x)):
        arr.append(x[-i - 1].__float__())
    return arr


# Sherman-Morrison algorithm implementation
def sherman_morrison(mat, sol):
    n = len(sol)
    u = [1] + [0] * (n - 2) + [1]
    v = [1] + [0] * (n - 2) + [1]

    mat[0][0] -= 1
    mat[n - 1][n - 1] -= 1
    mat[n - 1][0] = 0
    mat[0][n - 1] = 0
    y = np.array(thomas(mat, sol))
    z = np.array(thomas(mat, u))
    x = y - (np.dot(np.array(v), y)) / (1 + np.dot(np.array(v), z)) * z
    return x


if __name__ == '__main__':
    with open('out.txt', "w") as fd:
        fd.write(show_matrix(matrix, d))
        res = sherman_morrison(matrix, d)
        for index in range(len(d)):
            fd.write("x{0}: {1:.16f}\n".format(index + 1, res[index]))
