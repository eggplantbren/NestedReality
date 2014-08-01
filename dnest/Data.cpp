#include "Data.h"
#include "Ranks.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# Error opening file "<<filename<<"."<<endl;
		return;
	}

	// Empty the vectors
	logl.resize(0);

	// Read data from file
	double temp1;
	double temp2;
	int i=0;
	while(fin>>temp1)
	{
		logl.push_back(vector<double>());
		for(int j=0; j<static_cast<int>(temp1); j++)
		{
			fin>>temp2;
			logl[i].push_back(temp2);
		}
		cout<<"# Loaded run "<<(i+1);
		cout<<" with "<<logl[i].size()<<" points.";
		cout<<endl;
		i++;
	}
	fin.close();

	ranks = calculate_ranks(logl);
}

