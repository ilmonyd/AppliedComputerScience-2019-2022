from matplotlib import pyplot as plt
from numpy.polynomial import Polynomial
import numpy as np

x = [0.062500, 0.187500, 0.312500, 0.437500, 0.562500, 0.687500, 0.812500, 0.937500]
y = [0.687959, 0.073443, -0.517558, -1.077264, -1.600455, -2.080815, -2.507266, -2.860307]

mat = np.zeros((len(x), len(x)))
for i in range(len(x)):
    for j in range(len(x)):
        mat[i][j] = pow(x[i], j)

M = mat.T.tolist()

coeffs = [np.linalg.det((M+[y]+M)[d:d+len(x)]) for d in range(len(x)+1)]
coeffs = (coeffs / coeffs[0] * (-1)**(len(x)+1))[1:]

poly = Polynomial(coeffs, [-1, 1])

x1 = np.linspace(-1, 1, 100)
y1 = poly(x1)

if __name__ == '__main__':
    with open("out.txt", "w") as fd:
        for i in range(len(coeffs)):
            fd.write("{0} = {1:.4f}\n".format(chr(97+i), coeffs[i]))

    plt.plot(x, y, "or", label="Punkty wejściowe")
    plt.plot(x1, y1, "b", label="Funkcja interpolacyjna")
    plt.xlim(-1, 1)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("Zadanie numeryczne nr 6")
    plt.legend()
    plt.savefig("plot.png")
