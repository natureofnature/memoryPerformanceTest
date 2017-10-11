
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

smid = [long(l.split()[0]) for l in open("CUTCP_output.dat")]
smid_1 = [long(l.split()[0]) for l in open("LBM_OUTPUT.dat")]
start_time= [long(l.split()[1]) for l in open("CUTCP_output.dat")]
start_time_1= [long(l.split()[1]) for l in open("LBM_OUTPUT.dat")]
end_time= [long(l.split()[2]) for l in open("CUTCP_output.dat")]
end_time_1= [long(l.split()[2]) for l in open("LBM_OUTPUT.dat")]
duration = [end_time[i]-start_time[i] for i in range(len(smid))]
duration_1 = [end_time_1[i]-start_time_1[i] for i in range(len(smid_1))]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = smid
y = start_time
z = [0 for t in range(len(smid))]
dx = 0.1 
dy = 5 
dz = duration 

ax.bar3d(x, y, z, dx, dy, dz, color='blue')
x = smid_1
y = start_time_1
z = [0 for t in range(len(smid_1))]
dz = duration_1
ax.bar3d(x, y, z, dx, dy, dz, color='blue')
plt.show()
