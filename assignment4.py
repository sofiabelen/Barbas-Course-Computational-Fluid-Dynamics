import matplotlib.pyplot as plt
import numpy as np
import sympy
import seaborn as sns
from mpl_toolkits import mplot3d
from sympy.utilities.lambdify import lambdify

x, nu, t = sympy.symbols('x nu t')
phi = (sympy.exp(-(x - 4 * t)**2 / (4 * nu * (t + 1))) +
       sympy.exp(-(x - 4 * t - 2 * sympy.pi)**2 / (4 * nu * (t + 1))))

phiprime = phi.diff(x)

u = -2 * nu *(phiprime / phi) + 4

ufunc = lambdify((t, x, nu), u)

param = np.loadtxt('Parameters/input4')

nx = int(param[0])
nt = int(param[1])
nu = param[2]
dx = 2.0 / float(nx - 1)
dt = dx * nu

x = np.linspace(0, 2 * np.pi, nx)
u = np.zeros(shape=(nt, nx))
u_analytical = np.zeros(shape=(nt, nx))

u[0] = np.asarray([ufunc(0, i, nu) for i in x])

u[0][-1] = u[0][0]
u_analytical[nt - 1] = np.asarray([ufunc((nt - 1) * dt, i, nu) for i in x])

for t in range(0, nt - 1):
    for i in range(1, nx - 1):
        u[t + 1][i] = u[t][i] - u[t][i] * dt / dx * (u[t][i] -\
                u[t][i - 1]) + nu * dt / dx**2 * (u[t][i + 1] - 2 *\
                u[t][i] + u[t][i - 1])

    u[t + 1][0] = u[t][0] - u[t][0] * dt / dx * (u[t][0] -\
            u[t][-2]) + nu * dt / dx**2 * (u[t][1] - 2 *\
            u[t][0] + u[t][-2])
    u[t + 1][-1] = u[t + 1][0]
    u_analytical[t] = np.asarray([ufunc(t * dt, i, nu) for i in x])


y = np.arange(0, nt) * dt
x2, y2 = np.meshgrid(x, y)

fig3d = plt.figure()
ax3d = fig3d.gca(projection='3d')

ax3d.plot_surface(x2, y2, u, alpha=0.6)

ax3d.set_xlabel('Distance')
ax3d.set_ylabel('Time')
ax3d.set_zlabel(r'$u(i, t)$')
ax3d.set_title('Burgers\' Equation')
ax3d.set_yticks([0, nt / 2 * dt, (nt - 1) * dt])

sns.set(context='notebook', style='darkgrid', palette='Paired')

fig, ax = plt.subplots()

ax.plot(x, u[0], lw=2, label='Starting Condition')
ax.plot(x, u[nt - 1], marker='o', lw=2, label='Numerical Solution')
ax.plot(x, u_analytical[nt - 1], lw=2, label='Analytical Solution')
ax.set_ylim([0, 10])
ax.set_xlim([0, 2 * np.pi])
ax.set_title('Burgers\' Equation')
ax.legend(loc='best')

ax.set_xlabel('Distance')
ax.set_ylabel(r'$u(x)$')

fig.savefig('Images/assigment4.svg')
fig.savefig('Images/assigment4.png')

plt.show()
