#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

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
	logl.resize(0); ids.resize(0);

	// Read data from file
	double temp1, temp2;
	while(fin>>temp1 && fin>>temp2)
	{
		logl.push_back(temp1);
		ids.push_back(static_cast<int>(temp2));
	}

	fin.close();
}

