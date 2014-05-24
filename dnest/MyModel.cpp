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

double MyModel::perturb1()
{
	// Change alpha, leave logx values intact
	double logH = 0.;
	for(size_t j=1; j<logx[1].size(); j++)
		logH -= (logx[1][j] - logx[1][j-1])/alpha - log(alpha);

	alpha += randh();
	alpha = mod(alpha, 1.);

	for(size_t j=1; j<logx[1].size(); j++)
		logH += (logx[1][j] - logx[1][j-1])/alpha - log(alpha);

	return logH;
}

double MyModel::perturb()
{
	double logH = 0.;

	logH += perturb1();

	return logH;
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

