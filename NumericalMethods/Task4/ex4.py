#
#   Created by Oleg Semenov on 21.11.2020
#

import numpy as np
import scipy.sparse.linalg as la

ITERATION_LIMIT = 1000

matrix = np.zeros((128, 128))

for i in range(128):
    matrix[i][i] = 4
for i in range(127):
    matrix[i + 1][i] = 1
    matrix[i][i + 1] = 1
for i in range(124):
    matrix[i][i + 4] = 1
    matrix[i + 4][i] = 1

b = np.ones(128)

x = np.zeros_like(b)
for it_count in range(ITERATION_LIMIT):
    x_new = np.zeros_like(x)

    for i in range(matrix.shape[0]):
        s1 = np.dot(matrix[i, :i], x_new[:i])
        s2 = np.dot(matrix[i, i + 1:], x[i + 1:])
        x_new[i] = (b[i] - s1 - s2) / matrix[i, i]

    if np.allclose(x, x_new, rtol=1e-8):
        break

    x = x_new

with open("out_gs.txt", "w") as fd:
    fd.write("Solution:" + '\n')
    for i in range(128):
        fd.write("x" + str(i) + " = " + str(x[i]) + "\n")

sol = la.cg(matrix, b)

with open("out_cg.txt", "w") as fd:
    fd.write("Solution:" + '\n')
    for i in range(128):
        fd.write("x" + str(i) + " = " + str(sol[0][i]) + "\n")
