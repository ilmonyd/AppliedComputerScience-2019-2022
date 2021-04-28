import numpy as np
import matplotlib.pyplot as py
import scipy.stats as st


def gen_poiss(mi, NT, N):
    p = mi / NT
    r = np.random.rand(N, NT)
    k = np.sum(r <= p, axis=1)
    return k


mi = 4
N = 100000
NT = 1000
x = gen_poiss(mi, NT, N)
py.hist(x, bins=np.arange(int(x.max() + 1)) - 0.5, density=True)


p = mi / NT
k = np.arange(x.max() + 1)
P = st.poisson.pmf(k, mi)
py.plot(k, P, 'r+')
py.show()
