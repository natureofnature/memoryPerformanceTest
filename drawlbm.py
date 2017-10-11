
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
smid = [long(l.split()[0]) for l in open("LBM_OUTPUT.dat")]
start_time= [long(l.split()[1]) for l in open("LBM_OUTPUT.dat")]
end_time= [long(l.split()[2]) for l in open("LBM_OUTPUT.dat")]
print len(smid),len(start_time),len(end_time)
duration = [end_time[i]-start_time[i] for i in range(len(smid))]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = smid
y = start_time
z = [0 for t in range(len(smid))]

# Construct arrays for the anchor positions of the 16 bars.
# Note: np.meshgrid gives arrays in (ny, nx) so we use 'F' to flatten xpos,
# ypos in column-major order. For numpy >= 1.7, we could instead call meshgrid
# with indexing='ij'.

# Construct arrays with the dimensions for the 16 bars.
dx = 0.1 
dy = 5 
dz = duration 

ax.bar3d(x, y, z, dx, dy, dz, color='blue')

plt.show()
