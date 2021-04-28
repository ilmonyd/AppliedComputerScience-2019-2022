#
#   Created by Oleg Semenov on 24.10.2020
#   This is a simple program for solving tridiagonal using a Thomas algorithm
#

from fractions import Fraction

matrix = [[4, 1, 0, 0, 0, 0, 0],
          [1, 4, 1, 0, 0, 0, 0],
          [0, 1, 4, 1, 0, 0, 0],
          [0, 0, 1, 4, 1, 0, 0],
          [0, 0, 0, 1, 4, 1, 0],
          [0, 0, 0, 0, 1, 4, 1],
          [0, 0, 0, 0, 0, 1, 4]]

d = [1, 2, 3, 4, 5, 6, 7]


def beta(mat):
    arr = [Fraction(-mat[0][1], mat[0][0])]
    for i in range(1, len(mat) - 1):
        arr.append(Fraction(Fraction(-mat[i][i + 1]), Fraction(mat[i][i - 1]) * arr[i - 1] + Fraction(mat[i][i])))
    arr.append(Fraction(0))
    return arr


def gamma(mat, b, sol):
    arr = [Fraction(sol[0], mat[0][0])]
    for i in range(1, len(mat)):
        arr.append(Fraction(sol[i] - (mat[i][i - 1] * arr[i - 1]), (mat[i][i - 1] * b[i - 1]) + mat[i][i]))
    return arr


def show_matrix(mat, sol):
    arr = []
    for i in range(len(mat)):
       arr.append("|  {}| |  {}  | |  {}  |{}".format((''.join([str(num) + "  " for num in mat[i]])), 'x' + str(i+1), sol[i], '' if (i + 1) % len(mat) else '\n'*2))
    return '\n'.join(arr)


def thomas(mat, sol):
    b = beta(mat)
    g = gamma(mat, b, sol)
    x = [g[-1]]
    res = []
    for i in range(2, len(mat) + 1):
        x.append(Fraction(b[len(mat) - i] * x[i - 2]) + g[len(mat) - i])
    for i in range(len(x)):
        res.append("x{0}: {1:.20f}\n".format(i + 1, x[-i - 1].__float__()))
    return ''.join(res)


if __name__ == '__main__':
    with open("out.txt", "w") as fd:
        fd.write(show_matrix(matrix, d))
        fd.write(thomas(matrix, d))
