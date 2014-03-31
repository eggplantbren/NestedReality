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



class Model:
  """
  An object of this class is a hypothesis about the
  logx-values of all of the points. NB: I use 'S' instead of self
  """
  def __init__(S):
    pass

  @staticmethod
  def set_data(run_id, logl):
    """
    Keep a copy of the data in the Model class
    """
    Model.run_id, Model.logl = run_id, logl
    Model.order = np.argsort(Model.logl)

  def initialise(S):
    """
    Initialise the object in a way that is consistent
    with the ordering of the data. Note this does not
    draw from the prior.
    """
    pass

if __name__ == '__main__':
  rng.seed(1)
  run_id, logx, logl = simulate_data()
  Model.set_data(run_id, logl)

  plt.plot(logx[run_id==0], logl[run_id==0], 'bo-', alpha=0.2)
  plt.plot(logx[run_id==1], logl[run_id==1], 'ro-', alpha=0.2)
  plt.xlabel(r'$\log X$')
  plt.ylabel(r'$\log L$')
  plt.show()

