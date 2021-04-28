#
#   Created by Oleg Semenov on 12.11.2020
#

import numpy as np
import scipy.linalg as la

A = np.array([[-116.66654, 583.33346, -333.33308, 100.00012, 100.00012],
             [583.33346, -116.66654, -333.33308, 100.00012, 100.00012],
             [-333.33308, -333.33308, 133.33383, 200.00025, 200.00025],
             [100.00012, 100.00012, 200.00025, 50.000125, -649.99988],
             [100.00012, 100.00012, 200.00025, -649.99988, 50.000125]])

B = [
    np.array([[-0.33388066],
              [1.08033290],
              [-0.98559856],
              [1.31947922],
              [-0.09473435]]),
    np.array([[-0.33388066],
              [1.08033290],
              [-0.98559855],
              [1.32655028],
              [-0.10180541]]),
    np.array([[0.72677951],
              [0.72677951],
              [-0.27849178],
              [0.96592583],
              [0.96592583]]),
    np.array([[0.73031505],
              [0.73031505],
              [-0.27142071],
              [0.96946136],
              [0.96946136]])
     ]

if __name__ == '__main__':

    Z = []
    for i in range(4):
        Z.append(la.solve(A, B[i]))

    with open('out.txt', "w") as fd:
        for i in range(4):
            fd.write("z{}\n".format(i+1))
            for num in Z[i]:
                fd.write(str(num) + "\n")
            fd.write("\n")
        fd.write("\n")

        fd.write("||b1 - b2||\n")
        temp1 = la.norm(np.subtract(B[0], B[1]))
        fd.write(str(temp1) + "\n" * 2)

        fd.write("||b3 - b4||\n")
        temp2 = la.norm(np.subtract(B[2], B[3]))
        fd.write(str(temp2) + "\n" * 2)

        fd.write("||z1 - z2|| / ||b1 - b2||\n")
        fd.write(str(la.norm(np.subtract(Z[0], Z[1])) / temp1) + "\n" * 2)

        fd.write("||z3 - z4|| / ||b3 - b4||\n")
        fd.write(str(la.norm(np.subtract(Z[2], Z[3])) / temp2) + "\n" * 2)

