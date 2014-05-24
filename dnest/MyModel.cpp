#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:logx(Data::get_instance().get_logl())
{

}

void MyModel::fromPrior()
{
	alpha = randomU();

	double a;
	for(size_t i=0; i<logx.size(); i++)
	{
		logx[i][0] = log(randomU());
		a = (i == 0)?(1.):(alpha);
		for(size_t j=1; j<logx[i].size(); j++)
			logx[i][j] = logx[i][j-1] + a*log(randomU());
	}
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

