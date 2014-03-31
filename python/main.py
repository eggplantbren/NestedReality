import numpy as np
import matplotlib.pyplot as plt
import numpy.random as rng

def simulate_data():
  """
  Simulate some fake data
  """
  # Make a good run and a bad run
  run_id = np.ones(100).astype('int64')
  run_id[0:50] = 0

  logx = np.empty(100)
  logx[0:50] = np.cumsum(np.log(rng.rand(50)))
  logx[50:] = np.cumsum(0.5*np.log(rng.rand(50)))

  logl = np.sqrt(-logx)
  return [run_id, logx, logl]


if __name__ == '__main__':
  rng.seed(1)
  run_id, logx, logl = simulate_data()

  plt.plot(logx[run_id==0], logl[run_id==0], 'bo-', alpha=0.2)
  plt.plot(logx[run_id==1], logl[run_id==1], 'ro-', alpha=0.2)
  plt.show()

