import numpy as np
import matplotlib.pyplot as plt
import numpy.random as rng
import copy as cp

def simulate_data():
  """
  Simulate some fake data
  """
  # Make a good run and a bad run
  run_id = np.ones(100).astype('int64')
  run_id[0:50] = 0

  logx = np.empty(100)
  logx[0:50] = np.cumsum(np.log(rng.rand(50)))
  logx[50:] = 0.5*np.cumsum(np.log(rng.rand(50)))

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
    # logl gets sorted at this point
    Model.run_id, Model.logl = run_id, np.sort(logl)

  def initialise(S):
    """
    Initialise the object in a way that is consistent
    with the ordering of the data. Note this does not
    draw from the prior.
    """
    S.u = rng.rand(Model.logl.size)
    S.lam = 0.5

    S.logx = np.empty(Model.logl.size)
    for i in xrange(0, Model.run_id.max() + 1):
      which = (Model.run_id==i)
      if i==0:
        factor = 1.
      else:
        factor = S.lam
      S.logx[which] = factor*np.cumsum(np.log(S.u[which]))
    S.order = np.argsort(S.logx)
    S.logx = np.sort(S.logx)[::-1]

  def proposal(S):
    """
    Do a Metropolis proposal
    """
    if rng.rand() <= 0.5:
      index = rng.randint(S.u.size)
      S.u[index] += 10.**(1.5 - 6.*rng.rand())*rng.randn()
      S.u[index] = np.mod(S.u[index], 1.)
    else:
      S.lam += 10.**(1.5 - 6.*rng.rand())*rng.randn()
      S.lam = np.mod(S.lam, 1.)

    S.logx = np.empty(Model.logl.size)
    for i in xrange(0, Model.run_id.max() + 1):
      which = (Model.run_id==i)
      if i==0:
        factor = 1.
      else:
        factor = S.lam
      S.logx[which] = factor*np.cumsum(np.log(S.u[which]))
    S.order = np.argsort(S.logx)
    S.logx = np.sort(S.logx)[::-1]

if __name__ == '__main__':
  # Generate some fake data
  rng.seed(1)
  run_id, logx, logl = simulate_data()
  Model.set_data(run_id, logl)

  # Plot the truth
  plt.plot(logx[run_id==0], logl[run_id==0], 'bo-', alpha=0.2)
  plt.plot(logx[run_id==1], logl[run_id==1], 'ro-', alpha=0.2)
  plt.xlabel(r'$\log X$')
  plt.ylabel(r'$\log L$')
  plt.title('Reality')
  plt.show()

  # Now attempt to reconstruct it
  m = Model()
  m.initialise()

  # MCMC run length
  steps = 10000000
  skip = 1000
  keep = np.empty(steps//skip)

  plt.ion()
  plt.hold(False)
  for i in xrange(0, steps):
    mm = cp.deepcopy(m)
    mm.proposal()
    if np.all(mm.order == m.order):
      m = mm

    if i%skip == 0:
      keep[i//skip] = m.lam
      plt.plot(keep[0:(i//skip + 1)])
#      plt.plot(m.logx, Model.logl, 'bo')
#      plt.xlim([-80., 0.])
      print(keep[0:(i//skip + 1)].mean(), keep[0:(i//skip + 1)].std())
      plt.draw()

  plt.ioff()
  plt.show()

