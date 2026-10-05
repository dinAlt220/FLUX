import numpy as np
import matplotlib.pyplot as plt

def spect(theta, E):

	A = 18000.0
	B = 1.265
	alpha = -3.915
	beta = 1.165

	return A * (E + B)**alpha * E**beta * np.sin(theta) * np.cos(theta)

E = np.arange(1.0, 1e5, 1.0)
theta = 1.0 * np.pi / 180.0

E1 = np.arange(1,15,1)
E2 = np.arange(15,25,1)

I1 = 0.0
I2 = 0.0

for i in range(E1.shape[0] - 1):
	I1 = I1 + 0.5 * (spect(theta, E1[i]) + spect(theta, E1[i+1])) * 1.0

for i in range(E2.shape[0] - 1):
	I2 = I2 + 0.5 * (spect(theta, E2[i]) + spect(theta, E2[i+1])) * 1.0

print(I1)
print(I2)
print(I1 / I2)

plt.plot(E, spect(theta, E))
plt.xscale("log")
plt.yscale("log")
plt.show()