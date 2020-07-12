import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d

z = np.loadtxt('Data/output1')

dt = 0.01
dx = 0.1

# x is the position axis
# y is the time axis
# z is the value of u

y = np.arange(0, 100) * dt
x = np.arange(0, 20) * dx

x, y = np.meshgrid(x, y)

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.plot_surface(x, y, z)

ax.set_xlabel('Distance')
ax.set_ylabel('Time')
ax.set_zlabel(r'$u(i, t)$')
ax.set_title(r'$u(x,t)$')

plt.show()
