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


double MyModel::perturb2()
{
	// Change alpha, change logx values as well
	double ratio = 1./alpha;
	alpha += randh();
	alpha = mod(alpha, 1.);
	ratio *= alpha;

	for(size_t j=1; j<logx[1].size(); j++)
		logx[1][j] = logx[0][j] + (logx[1][j] - logx[0][j])*ratio;

	return 0.;
}


double MyModel::perturb3()
{
	double logH = 0.;

	// Change logx values, leave alpha intact
	int i = randInt(logx.size());
	int j = randInt(logx[i].size());

	double lower = (j == static_cast<int>(logx[i].size()))?
				(-1E300):(logx[i][j+1]);
	double upper = (j == 0)?(0.):(logx[i][j-1]);

	logH -= logx[i][j];
	logx[i][j] += randh();
	logH += logx[i][j];

	if(logx[i][j] < lower || logx[i][j] > upper)
		logH = -1E300;

	return logH;
}

double MyModel::perturb()
{
	double logH = 0.;

	int which = randInt(3);

	if(which == 0)
		logH += perturb1();
	else if(which == 1)
		logH += perturb2();
	else
		logH += perturb3();

	return logH;
}

double MyModel::logLikelihood() const
{
	return 0.;
}

void MyModel::print(std::ostream& out) const
{
	out<<alpha<<' ';
	for(size_t i=0; i<logx.size(); i++)
		for(size_t j=0; j<logx[i].size(); j++)
			out<<logx[i][j]<<' ';
}

string MyModel::description() const
{
	return string("alpha");
}

