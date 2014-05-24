from pylab import *

seed(0)

# Number of runs
N = 2

# Number of particles per run
n = 100

# Generate the data
u = empty((n, N))
ids = empty((n, N)).astype('int64')

for i in xrange(0, N):
  if i != N-1:
    # Good run
    u[:, i] = cumsum(-log(1. - rand(n)))
    ids[:,i] = 0
  else:
    # Bad run
    u[0, i] = -log(1. - rand(1))
    u[1:, i] = -0.5*log(1. - rand(n-1))
    u[:, i] = cumsum(u[:,i])
    ids[:,i] = 1


# NEW DATA FORMAT. EACH RUN GOES ON ONE ROW
data = empty((N, n+1))
data[:,0] = n
data[:,1:] = u.T
savetxt('data.txt', data)

### ALTERNATIVE DATA FORMAT
#u = u.flatten()
#ids = ids.flatten()
#sortkey = argsort(u)
#u = u[sortkey]
#ids = ids[sortkey]

#data = empty((N*n, 2))
## Likelihood function - we don't get to see 'u'
#data[:,0] = sqrt(u)
#data[:,1] = ids
#print(data)
#savetxt('data.txt', data)


