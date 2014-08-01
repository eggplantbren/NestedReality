#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Ranks.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:s(Data::get_instance().get_logl())
{

}

void MyModel::calculate_logp()
{
	logp = 0.;

	double a;
	for(size_t i=0; i<s.size(); i++)
	{
		a = (i == 0)?(1.):(alpha);

		if(s[i][0] < 0)
		{
			logp = -1E300;
			break;
		}
		for(size_t j=1; j<s[i].size(); j++)
		{
			if(s[i][j] < s[i][j-1])
			{
				logp = -1E300;
				break;
			}
			logp += -(s[i][j] - s[i][j-1])/a - log(a);
		}
	}
}

void MyModel::fromPrior()
{
	alpha = 0.1 + randomU();

	double a;
	for(size_t i=0; i<s.size(); i++)
	{
		s[i][0] = -log(randomU());
		a = (i == 0)?(1.):(alpha);
		for(size_t j=1; j<s[i].size(); j++)
			s[i][j] = s[i][j-1] - a*log(randomU());
	}
	calculate_logp();
}

double MyModel::perturb1()
{
	// Change alpha, leave s values intact
	double logH = -logp;

	alpha += 0.9*randh();
	alpha = mod(alpha - 0.1, 0.9) + 0.1;

	calculate_logp();
	logH += logp;

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

	calculate_logp();
	return 0.;
}


double MyModel::perturb3()
{
	double logH = 0.;

	// Change s values, leave alpha intact
	int i = randInt(s.size());
	int j = randInt(s[i].size());

	logH -= -logp;
	s[i][j] += randh();
	calculate_logp();
	logH += logp;

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
	const vector< vector<int> >& data = Data::get_instance().get_ranks();
	vector< vector<int> > ranks = calculate_ranks(s);

	assert(data.size() == ranks.size());

	long double logL = 0.;
	for(size_t i=0; i<data.size(); i++)
	{
		assert(data[i].size() == ranks[i].size());
		for(size_t j=0; j<data[i].size(); j++)
		{
			logL += -pow(ranks[i][j] - data[i][j], 2);
		}
	}

	return (double)logL;
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

