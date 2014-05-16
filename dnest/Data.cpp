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

	fin.close();
}

