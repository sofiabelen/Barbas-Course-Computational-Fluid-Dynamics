import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
from matplotlib import cm

P = np.loadtxt('Data/output10_')
param = np.loadtxt('Parameters/input10')
exp_count = int(np.loadtxt('Parameters/counter')) - 1

dx = param[0]
nt = int(param[1])
dy = dx
nx = int(2.0 / dx)
ny = int(1.0 / dy)

print("dx: ", dx)
print("dy: ", dy)
print("nx: ", nx)
print("ny: ", ny)
print("nt: ", nt)

# P = P.reshape(nt, nx, ny)
P = P.reshape(nx, ny)

x = np.linspace(0, 2, nx)
y = np.linspace(0, 1, ny)
y, x = np.meshgrid(y, x)

rg1 = np.arange(0, 51, 10)
rg2 = np.arange(100, 501, 100)
rg3 = np.arange(1000, 4001, 1000)
rg4 = np.arange(5000, 10001, 5000)
rg = np.concatenate((rg1, rg2))
rg = np.concatenate((rg, rg3))
rg = np.concatenate((rg, rg4))

# for t in rg:
t = 0
t = int(t)
print(t)
fig = plt.figure(figsize=(11, 7), dpi=100)
ax = fig.gca(projection='3d')

ax.plot_surface(y, x, P, alpha=0.8, cmap=cm.viridis,\
        rstride=1, cstride=1, linewidth=0, antialiased=False)

ax.set_ylabel('x')
ax.set_xlabel('y')
ax.set_zlabel(r'$P(x, y)$')
ax.set_title(f'Poisson equation after {t} iterations')
ax.set_yticks(np.linspace(0, 2, 5))
ax.set_xticks(np.linspace(0, 1, 5))

fig.show()
input()
