import numpy as np
from math import sqrt
#np.set_printoptions(precision=9, suppress=False)


A = np.array([[22, -4], [10, -20], [-10, 20], [-22, 4]])

# SVD decomposition
U, S, V = np.linalg.svd(A)
b = np.array([[-4], [4], [2], [-3]])
# least squares solution
S_pinv = np.zeros((V.shape[0], U.shape[1]))
for i in range(len(S)):
    if S[i] > 1e-10:  # Avoid division by zero
        S_pinv[i, i] = 1 / S[i]
x = V.T @ S_pinv @ U.T @ b
print(x)