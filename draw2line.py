import numpy as np
import matplotlib  
matplotlib.use('Agg')    
import matplotlib.pyplot as plt
plt.figure(1)
import sys
numOfPara=len(sys.argv)
if numOfPara<5:
	print "You should specify the target file, and picture name"
	sys.exit(0)


y = [float(l.split()[0]) for l in open(sys.argv[1])]
x = [t for t in range(0,len(y))]
ma = max(y)

w = [float(l.split()[0]) for l in open(sys.argv[2])]
z = [t for t in range(0,len(w))]
mb = max(w)

mc = max(ma,mb)

axes = plt.gca()
axes.set_ylim([0,mc+1])

plt.plot(z, w,linewidth=1.0)
plt.plot(x, y,linewidth=1.0)

picturename = sys.argv[3]
title = sys.argv[4]
plt.title(title)
plt.savefig(picturename);
plt.show()

