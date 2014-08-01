#ifndef _Ranks_
#define _Ranks_

#include <vector>

std::vector< std::vector<int> > calculate_ranks(const std::vector< std::vector<double> >& values);

typedef struct
{
	const double* ptr;
	int i;
	int j;
}values_ptr;

bool operator < (const values_ptr& l1, const values_ptr& l2);

#endif

