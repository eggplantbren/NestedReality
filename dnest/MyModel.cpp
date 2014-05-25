#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:s(Data::get_instance().get_logl())
{

}

void MyModel::fromPrior()
{
	alpha = 0.1 + randomU();

	double a;
	for(size_t i=0; i<s.size(); i++)
	{
		s[i][0] = log(randomU());
		a = (i == 0)?(1.):(alpha);
		for(size_t j=1; j<s[i].size(); j++)
			s[i][j] = s[i][j-1] + a*log(randomU());
	}
}

double MyModel::perturb1()
{
	// Change alpha, leave s values intact
	double logH = 0.;
	for(size_t j=1; j<s[1].size(); j++)
		logH -= (s[1][j] - s[1][j-1])/alpha - log(alpha);

	alpha += 0.9*randh();
	alpha = mod(alpha - 0.1, 0.9) + 0.1;

	for(size_t j=1; j<s[1].size(); j++)
		logH += (s[1][j] - s[1][j-1])/alpha - log(alpha);

	return logH;
}


double MyModel::perturb2()
{
	// Change alpha, change s values as well
	double ratio = 1./alpha;
	alpha += 0.9*randh();
	alpha = mod(alpha - 0.1, 0.9) + 0.1;
	ratio *= alpha;

	for(size_t j=1; j<s[1].size(); j++)
		s[1][j] = s[1][0] + (s[1][j] - s[1][0])*ratio;

	return 0.;
}


double MyModel::perturb3()
{
	double logH = 0.;

	// Change s values, leave alpha intact
	int i = randInt(s.size());
	int j = randInt(s[i].size());

	double lower = (j == (static_cast<int>(s[i].size()) - 1))?
				(-1E300):(s[i][j+1]);
	double upper = (j == 0)?(0.):(s[i][j-1]);

	double a = (i == 0)?(1.):(alpha);

	logH -= s[i][0];
	for(size_t jj=1; jj<s[i].size(); jj++)
		logH -= (s[i][jj] - s[i][jj-1])/a;

	s[i][j] += randh();

	logH += s[i][0];
	for(size_t jj=1; jj<s[i].size(); jj++)
		logH += (s[i][jj] - s[i][jj-1])/a;

	if(s[i][j] < lower || s[i][j] > upper)
	{
		logH = -1E300;
		return logH;
	}

	return logH;
}

double MyModel::perturb()
{
	double logH = 0.;

	if(randomU() <= 0.05)
	{
		fromPrior();
		return 0.;
	}

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
	for(size_t i=0; i<s.size(); i++)
		for(size_t j=0; j<s[i].size(); j++)
			out<<s[i][j]<<' ';
}

string MyModel::description() const
{
	return string("alpha");
}

