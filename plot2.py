import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from mpl_toolkits import mplot3d
from matplotlib import cm

z = np.loadtxt('Data/output2')
param = np.loadtxt('Parameters/input2')
exp_count = int(np.loadtxt('Parameters/counter')) - 1

dx = param[0]
real_time = int(param[1])
sigma = param[2]
dt = dx * sigma
nt = int(real_time / dt)
nx = int(2.0 / dx)

print("dt: ", dt)
print("dx: ", dx)
print("nx: ", nx)
print("nt: ", nt)
print("real time: ", real_time)

x = np.arange(0, nx) * dx
y = np.arange(0, nt) * dt

x2, y2 = np.meshgrid(x, y)

fig3d = plt.figure(figsize=(11, 7), dpi=100)
ax3d = fig3d.gca(projection='3d')

ax3d.plot_surface(x2, y2, z, alpha=0.8, cmap=cm.viridis)

ax3d.set_xlabel('x')
ax3d.set_ylabel('t')
ax3d.set_zlabel(r'$u(i, t)$')
ax3d.set_title('1D Non-linear Convection')
ax3d.set_xticks(np.linspace(0, 2.0, 5))
ax3d.set_yticks(np.linspace(0, real_time, 5))

sns.set(context='notebook', style='darkgrid', palette='Paired')

fig, ax = plt.subplots()

for t in np.arange(0, real_time, 0.1):
    fig, ax = plt.subplots()
    
    ax.plot(x, z[0], lw=2, label='Starting Condition')
    ax.plot(x, z[int(t * float(nt) / float(real_time))],\
            lw=2, label=f'Numerical Solution after time = {float(t / 2.0):.1f}')
    ax.legend(loc='best')
    ax.set_xlabel('x')
    ax.set_ylabel(r'$u(x)$')
    ax.set_title('1D Non-Linear Convection')
    
    fig.savefig(f'Images/2-exp{exp_count}-time{t:.1f}.svg')
    fig.savefig(f'Images/2-exp{exp_count}-time{t:.1f}.png')

fig3d.show()
input()
