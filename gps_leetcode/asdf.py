import numpy as np
from math import sqrt
v1 = np.array([3, 0, 2, 0, 1, -1])
v2 = np.array([3, -4, 5, 0, 2, 0])
v3 = np.array([3, 0, 3, -4, 5, 0])

def inner_product(v1, v2):
    return sum(a * b for a, b in zip(v1, v2))

