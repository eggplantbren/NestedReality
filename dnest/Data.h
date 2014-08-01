#ifndef _Data_
#define _Data_

#include <vector>

class Data
{
	private:
		std::vector< std::vector<double> > logl;
		std::vector< std::vector<int> > ranks;

	public:
		Data();
		void load(const char* filename);

		const std::vector< std::vector<double> >& get_logl() const
		{ return logl; }
		const std::vector< std::vector<int> >& get_ranks() const
		{ return ranks; }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

