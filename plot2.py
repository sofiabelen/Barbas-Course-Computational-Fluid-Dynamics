import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from mpl_toolkits import mplot3d

z = np.loadtxt('Data/output2')
param = np.loadtxt('Parameters/input2')

nx = int(param[0])
nt = int(param[1])
dt = param[2]
dx = 2.0 / float(nx)

# x is the position axis
# y is the time axis
# z is the value of u

x = np.arange(0, nx) * dt
y = np.arange(0, nt) * dx

x2, y2 = np.meshgrid(x, y)

fig3d = plt.figure()
ax3d = fig3d.gca(projection='3d')

ax3d.plot_surface(x2, y2, z, alpha=0.6)

ax3d.set_xlabel('Distance')
ax3d.set_ylabel('Time')
ax3d.set_zlabel(r'$u(i, t)$')
ax3d.set_title('1D Non-linear Convection')

sns.set(context='notebook', style='darkgrid', palette='Paired')

fig, ax = plt.subplots()

ax.plot(x, z[0], lw=2, label='Starting Condition')
ax.plot(x, z[nt - 1], lw=2, label='Numerical Solution')
ax.legend(loc='best')
ax.set_xlabel('Distance')
ax.set_ylabel(r'$u(x)$')
ax.set_title('1D Non-linear Convection')

fig.savefig('Images/assigment2.svg')
fig.savefig('Images/assigment2.png')

plt.show()
