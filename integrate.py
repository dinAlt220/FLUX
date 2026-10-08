import numpy as np
import matplotlib.pyplot as plt

def spect(E):

	A = 1.4
	B = 1.265
	alpha = -3.915
	beta = 1.165

	return A * (E + B)**alpha * E**beta


def spect1(E):

	A = 18000.0
	B = 1.265
	alpha = -3.915
	beta = 1.165

	return E**-2.7


E = np.arange(1.0, 1e5, 1.0)

plt.plot(E, spect(E))
plt.plot(E, spect1(E))
plt.xscale("log")
plt.yscale("log")
plt.show()


# I1 = 0.0
# I2 = 0.0

# for i in range(E1.shape[0] - 1):
# 	I1 = I1 + 0.5 * (spect(theta, E1[i]) + spect(theta, E1[i+1])) * 1.0

# for i in range(E2.shape[0] - 1):
# 	I2 = I2 + 0.5 * (spect(theta, E2[i]) + spect(theta, E2[i+1])) * 1.0


# print(I1)
# print(I2)
# print(I1 / I2)
