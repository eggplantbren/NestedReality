#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
{

}

void MyModel::fromPrior()
{
	alpha = randomU();
}

double MyModel::perturb()
{
	alpha += randh();
	alpha = mod(alpha, 1.);

	return 0.;
}

double MyModel::logLikelihood() const
{
	return 0.;
}

void MyModel::print(std::ostream& out) const
{
	out<<alpha;
}

string MyModel::description() const
{
	return string("alpha");
}

