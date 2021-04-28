import numpy as np
import scipy.interpolate as sp
import matplotlib.pyplot as plt


def func(x):
    return 1 / (1 + 5 * pow(x, 2))


x = np.arange(-1, 1.0001, 1 / 32)
y = [func(num) for num in x]

xl = np.linspace(-1, 1, 85)
yl = np.array([])

for xn in xl:
    yn = 0
    for xi, yi in zip(x, y):
        p = np.prod((xn - x[x != xi]) / (xi - x[x != xi]))
        yn += yi * p
    yl = np.append(yl, yn)

tck = sp.splrep(x, y, s=0)
ycs = sp.splev(xl, tck)

plt.plot(xl, ycs, 'b', label="splajn kubiczny")
plt.plot(xl, yl, 'r--', label="wielomian interpolacyjny")
plt.xlabel("x")
plt.ylabel("y")
plt.title("Zadanie numeryczne nr 8")
plt.legend()
plt.show()

