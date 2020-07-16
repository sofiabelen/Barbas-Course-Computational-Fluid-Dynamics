import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
from matplotlib import cm

u = np.loadtxt('Data/output7')
param = np.loadtxt('Parameters/input7')

nx = int(param[0])
nt = int(param[1])
sigma = param[2]
nu = param[3]
dx = 2.0 / float(nx)
dt = sigma * dx * dx / nu

u = u.reshape((nt, nx, nx))

x = np.arange(0, nx) * dx
y = np.arange(0, nx) * dx

x2, y2 = np.meshgrid(x, y)

fig = plt.figure()
ax1 = fig.add_subplot(131, projection='3d')
ax2 = fig.add_subplot(132, projection='3d')
ax3 = fig.add_subplot(133, projection='3d')

fig.suptitle('2D Diffusion')

ax1.plot_surface(x2, y2, u[0], alpha=1, cmap=cm.viridis)
ax1.set_title('Starting Condition')
ax1.set_xlabel(r'$x$')
ax1.set_ylabel(r'$y$')
ax1.set_yticks(np.linspace(0, nx * dx, 5))
ax1.set_zlabel(r'$u(x, y, t)$')
ax1.set_xticks(np.linspace(0, 2, 5))
ax1.set_zticks(np.linspace(1, 2.25, 5))

ax2.plot_surface(x2, y2, u[int(nt / 2) - 1], alpha=1, cmap=cm.viridis)
ax2.set_title(f'After {int(nt/2)} timesteps')
ax2.set_xlabel(r'$x$')
ax2.set_ylabel(r'$y$')
ax2.set_yticks(np.linspace(0, nx * dx, 5))
ax2.set_zlabel(r'$u(x, y, t)$')
ax2.set_xticks(np.linspace(0, 2, 5))
ax2.set_zticks(np.linspace(1, 2.25, 5))

ax3.plot_surface(x2, y2, u[nt - 1], alpha=1, cmap=cm.viridis)
ax3.set_title(f'After {nt} timesteps')
ax3.set_xlabel(r'$x$')
ax3.set_ylabel(r'$y$')
ax3.set_yticks(np.linspace(0, nx * dx, 5))
ax3.set_zlabel(r'$u(x, y, t)$')
ax3.set_xticks(np.linspace(0, 2, 5))
ax3.set_zticks(np.linspace(1, 2.25, 5))

plt.show()
