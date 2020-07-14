import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from mpl_toolkits import mplot3d

u = np.loadtxt('Data/output3')
param = np.loadtxt('Parameters/input3')

nx = int(param[0])
nt = int(param[1])
dt = param[2]

x = np.linspace(0, 2, nx)
y = np.arange(0, nt) * dt
x2, y2 = np.meshgrid(x, y)

fig3d = plt.figure()
ax3d = fig3d.gca(projection='3d')

ax3d.plot_surface(x2, y2, u, alpha=0.6)

ax3d.set_xlabel('Distance')
ax3d.set_ylabel('Time')
ax3d.set_zlabel(r'$u(i, t)$')
ax3d.set_title('1D Diffusion')
ax3d.set_yticks([0, nt / 2 * dt, (nt - 1) * dt])

sns.set(context='notebook', style='darkgrid', palette='Paired')

fig, ax = plt.subplots()

ax.plot(x, u[0], lw=2, label='Starting Condition')
ax.plot(x, u[nt - 1], lw=2, label='Numerical Solution')
ax.legend(loc='best')
ax.set_xlabel('Distance')
ax.set_ylabel(r'$u(x)$')
ax.set_title('1D Diffusion')

fig.savefig('Images/assigment3.svg')
fig.savefig('Images/assigment3.png')

plt.show()
