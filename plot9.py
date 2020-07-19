import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
from matplotlib import cm

P = np.loadtxt('Data/output9')
param = np.loadtxt('Parameters/input9')
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

P = P.reshape(nt, nx, ny)

x = np.linspace(0, 2, nx)
y = np.linspace(0, 1, ny)
y, x = np.meshgrid(y, x)

for t in np.arange(0, 275, 25):
    print(t)
    t = int(t)
    fig = plt.figure(figsize=(11, 7), dpi=100)
    ax = fig.gca(projection='3d')

    ax.plot_surface(y, x, P[t], alpha=0.8, cmap=cm.viridis)

    ax.set_ylabel('x')
    ax.set_xlabel('y')
    ax.set_zlabel(r'$P(x, y)$')
    ax.set_title(f'Laplace equation after {t} iterations')
    ax.set_yticks(np.linspace(0, 2, 5))
    ax.set_xticks(np.linspace(0, 1, 5))

    fig.show()
    input()
