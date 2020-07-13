import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d

z = np.loadtxt('Data/output2')
param = np.loadtxt('Parameters/input2')

nx = param[0]
nt = param[1]
dt = param[2]
dx = 2.0 / float(nx)

# x is the position axis
# y is the time axis
# z is the value of u

x = np.arange(0, nx) * dt
y = np.arange(0, nt) * dx

x, y = np.meshgrid(x, y)

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.plot_surface(x, y, z, alpha=0.6)

ax.set_xlabel('Distance')
ax.set_ylabel('Time')
ax.set_zlabel(r'$u(i, t)$')
ax.set_title(r'$u(x,t)$')

plt.show()
