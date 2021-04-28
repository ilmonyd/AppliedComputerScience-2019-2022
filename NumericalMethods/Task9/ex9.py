import numpy as np
import random
import matplotlib.pyplot as plt

epsilon = 10e-8


class Point:
    def __init__(self, x, y):
        self.x, self.y = x, y

    def __lt__(self, other):
        return self.y < other.y


def func(x):
    return (pow(x, 2) - 1) * pow(np.sinh(x), 3)


def secant(p0, p1, N=1000, e=epsilon):
    x0, x1, x2 = p0.x, p1.x, 0
    step = 1
    condition = True
    while condition:
        if func(x0) == func(x1):
            break

        x2 = x0 - (x1 - x0) * func(x0) / (func(x1) - func(x0))
        x0 = x1
        x1 = x2
        step = step + 1

        if step > N:
            return "Non convergent"

        condition = abs(func(x2)) > e
    return x2


def inverse_interp(points):
    points = sorted(points)
    for point in points:
        point.x, point.y = point.y, point.x

    temp = 0

    while True:
        temp = 0
        for i, p1 in enumerate(points):
            inter = 1

            for j, p2 in enumerate(points):
                if i != j:
                    inter *= (-p2.x) / (p1.x - p2.x)

            temp += inter * p1.y

        points = points[1:3] + [Point(func(temp), temp)]

        if abs(func(points[2].y)) <= epsilon:
            break

    return temp


results_sec, results_inv = [], []

if __name__ == '__main__':
    for k in range(10):
        points = []
        for i in range(3):
            random.seed()
            x = random.uniform(0, 1)
            y = func(x)
            points.append(Point(x, y))
        for i in range(3):
            print(f"P{i + 1}: ({points[i].x}, {points[i].y})")

        print(f"Metoda siecznych: {secant(points[0], points[2])}, "
              f"{func(secant(points[0], points[2]))}")
        print(f"Interpolacja odwrotna: {inverse_interp(points)}, "
              f"{func(inverse_interp(points))}\n")
        results_inv.append(inverse_interp(points))
        results_sec.append(secant(points[0], points[2]))

    plt.plot(results_sec, [func(num) for num in results_sec], "b+", label="Secant method")
    plt.plot(results_inv, [func(num) for num in results_inv], "r+", label="Inverse interpolation method")
    plt.legend()
    plt.show()
