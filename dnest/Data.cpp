#include "Data.h"
#include <fstream>
#include <iostream>

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
	int temp1;
	double temp2;
	int i=0;
	while(fin>>temp1)
	{
		for(int j=0; j<temp1; j++)
		{
			fin>>temp2;
			logl[i].push_back(temp2);
		}
		i++;
	}
	fin.close();
}

