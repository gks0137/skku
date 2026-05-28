import numpy as np
from math import sqrt
v1 = np.array([3, 0, 2, 0, 1, -1])
v2 = np.array([3, -4, 5, 0, 2, 0])
v3 = np.array([3, 0, 3, -4, 5, 0])

def inner_product(v1, v2):
    return sum(a * b for a, b in zip(v1, v2))

u1 = v1
u1_v2 = inner_product(u1, v2)
u1_u1 = inner_product(u1, u1)
u2 = v2 - (u1_v2 / u1_u1) * u1
u1_v3 = inner_product(u1, v3)
u2_v3 = inner_product(u2, v3)
u2_u2 = inner_product(u2, u2)
u3 = v3 - (u1_v3 / u1_u1) * u1 - (u2_v3 / u2_u2) * u2
print("u1:", u1)
print("u1_v2:", u1_v2)
print("u1_u1:", u1_u1)
print("u2:", u2)
print("u2_v3:", u2_v3)
print("u2_u2:", u2_u2)
print("u3:", u3)