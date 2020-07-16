import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
from matplotlib import cm

u = np.loadtxt('Data/output6_1')
v = np.loadtxt('Data/output6_2')
param = np.loadtxt('Parameters/input6')

nx = int(param[0])
nt = int(param[1])
dt = param[2]
dx = 2.0 / float(nx)

u = u.reshape((nt, nx, nx))
v = v.reshape((nt, nx, nx))

x = np.arange(0, nx) * dx
y = np.arange(0, nx) * dx

x2, y2 = np.meshgrid(x, y)

fig = plt.figure(figsize=(22, 7), dpi=100)
ax1 = fig.add_subplot(121, projection='3d')
ax2 = fig.add_subplot(122, projection='3d')

fig.suptitle('2D Convection')

ax1.plot_surface(x2, y2, u[0], alpha=1, cmap=cm.viridis)
ax1.set_title('Starting Condition')
ax1.set_xlabel(r'$x$')
ax1.set_ylabel(r'$y$')
ax1.set_yticks(np.linspace(0, nx * dx, 5))
ax1.set_zlabel(r'$u(x, y, t)$')
ax1.set_xticks(np.linspace(0, 2, 5))

ax2.plot_surface(x2, y2, u[nt - 1], alpha=1, cmap=cm.viridis)
ax2.set_title('Numerical Solution')
ax2.set_xlabel(r'$x$')
ax2.set_ylabel(r'$y$')
ax2.set_yticks(np.linspace(0, nx * dx, 5))
ax2.set_zlabel(r'$u(x, y, t)$')
ax2.set_xticks(np.linspace(0, 2, 5))

plt.show()
