from pylab import *

# Check the prior
sample = loadtxt('sample.txt')

logx = sample[:, 1:101]
diff = (logx[:,1:] - logx[:,0:-1]).flatten()
hist(diff.flatten(), 100)
title('Histogram of differences, run 1')
print(diff.mean(), diff.std())
show()

