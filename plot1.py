import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from mpl_toolkits import mplot3d
from matplotlib import cm

z = np.loadtxt('Data/output1')
param = np.loadtxt('Parameters/input1')

nx = int(param[0])
nt = int(param[1])
dt = param[2]
dx = 2.0 / float(nx)

# x is the position axis
# y is the time axis
# z is the value of u

x = np.arange(0, nx) * dx
y = np.arange(0, nt) * dt

x2, y2 = np.meshgrid(x, y)

fig3d = plt.figure(figsize=(11, 7), dpi=100)
ax3d = fig3d.gca(projection='3d')

ax3d.plot_surface(x2, y2, z, alpha=0.8, cmap=cm.viridis)

ax3d.set_xlabel('Distance')
ax3d.set_ylabel('Time')
ax3d.set_zlabel(r'$u(i, t)$')
ax3d.set_title('1D Linear Convection')
ax3d.set_xticks(np.linspace(0, 2, 5))

sns.set(context='notebook', style='darkgrid', palette='Paired')

fig, ax = plt.subplots()

ax.plot(x, z[0], lw=2, label='Starting Condition')
ax.plot(x, z[nt - 1], lw=2, label='Numerical Solution')
ax.legend(loc='best')
ax.set_xlabel('Distance')
ax.set_ylabel(r'$u(x)$')
ax.set_title('1D Linear Convection')

fig.savefig('Images/assigment1.svg')
fig.savefig('Images/assigment1.png')

plt.show()
