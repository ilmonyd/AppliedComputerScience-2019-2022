#
#   Created by Oleg Semenov on 28.11.2020
#

import numpy as np
import scipy.sparse.linalg as la

matrix = np.ones((64, 64))

for i in range(64):
    matrix[i][i] = 5
for i in range(63):
    matrix[i + 1][i] = 2
    matrix[i][i + 1] = 2
for i in range(60):
    matrix[i][i + 4] = 2
    matrix[i + 4][i] = 2

b = np.ones(64)


def sherman_morrison(mat, sol):
    u = np.ones(64)
    v = np.ones(64)

    for i in range(64):
        for j in range(64):
            mat[i][j] -= 1

    y = np.array(la.cg(mat, sol)[0])
    z = np.array(la.cg(mat, u)[0])
    x = y - (np.dot(np.array(v), y)) / (1 + np.dot(np.array(v), z)) * z
    return x


if __name__ == '__main__':
    with open("out.txt", 'w') as fd:
        res = sherman_morrison(matrix, b)
        for i in range(len(res)):
            fd.write("x{0} = {1:.16f}\n".format(i, res[i]))
