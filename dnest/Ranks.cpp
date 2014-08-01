#include "Ranks.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool operator < (const values_ptr& l1, const values_ptr& l2)
{
	return *(l1.ptr) < *(l2.ptr);
}

vector< vector<int> > calculate_ranks(const vector< vector<double> >& values)
{
	vector< vector<int> > ranks(values.size());
	for(size_t i=0; i<values.size(); i++)
		ranks[i].assign(values[i].size(), 0);

	vector< values_ptr > pointers;
	values_ptr temp;
	for(size_t i=0; i<values.size(); i++)
	{
		for(size_t j=0; j<values[i].size(); j++)
		{
			temp.ptr = &(values[i][j]);
			temp.i = i; temp.j = j;
			pointers.push_back(temp);
		}
	}

	sort(pointers.begin(), pointers.end());

	for(size_t i=0; i<pointers.size(); i++)
		ranks[pointers[i].i][pointers[i].j] = i;

	return ranks;
}

