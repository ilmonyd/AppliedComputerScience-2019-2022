#!/usr/bin/env python3

import matplotlib.pyplot as plt
import random


def pdf(x):
    if x < -1:
        return 0
    if x < 0:
        return x/3 + 1/3
    if x < 2:
        return 1/3
    if x < 3:
        return 1 - x/3
    else:
        return 0


def sample(pdf, count=1, xmin=0.0, xmax=1.0, ymax=1.0):
    samples = []

    while len(samples) < count:
        x = random.uniform(xmin, xmax)
        y = random.uniform(0, ymax)
        if y <= pdf(x):
            samples.append(x)

    return samples if count > 1 else samples[0]


X = [-2, -1, 0, 2, 3, 4]
samples = sample(pdf, 10000, -2, 4, 1/3)

plt.hist(samples, bins=100, density=True)
plt.plot(X, [pdf(x) for x in X], color='orange')
plt.ylim((0, 1))
plt.grid()
plt.show()