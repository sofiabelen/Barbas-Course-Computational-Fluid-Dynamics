import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
from matplotlib import cm
import seaborn as sns

u = np.loadtxt('Data/u11')
v = np.loadtxt('Data/v11')
P = np.loadtxt('Data/p11')
param = np.loadtxt('Parameters/input11')
exp_count = int(np.loadtxt('Parameters/counter')) - 1

dx = param[0]
dt = param[1]
dy = dx
real_time = param[2]
nx = int(2.0 / dx)
ny = int(2.0 / dy)
nt = int(real_time / dt)

print("dx: ", dx)
print("dy: ", dy)
print("dt: ", dt)
print("nx: ", nx)
print("ny: ", ny)
print("nt: ", nt)

u = u.reshape(nx, ny)
v = v.reshape(nx, ny)
P = P.reshape(nx, ny)
u = np.transpose(u)
v = np.transpose(v)
P = np.transpose(P)

x = np.linspace(0, 2, nx)
y = np.linspace(0, 2, ny)
x, y = np.meshgrid(x, y)

sns.set(context='notebook', style='dark')

fig = plt.figure(figsize=(11, 7), dpi=100)
plt.contourf(x, y, P, alpha=0.5, cmap=cm.viridis)
plt.colorbar(label='Pressure')
plt.contour(x, y, P, cmap=cm.viridis)
plt.quiver(x[::2, ::2], y[::2, ::2], u[::2, ::2], v[::2, ::2],\
        label='Velocity')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Cavity-Flow with Navier-Stokes')
plt.legend(loc='lower left')

fig.savefig(f'Images/11-exp{exp_count}.svg')
fig.savefig(f'Images/11-exp{exp_count}.png')

plt.show()
