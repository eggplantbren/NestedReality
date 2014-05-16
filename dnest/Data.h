#ifndef _Data_
#define _Data_

#include <vector>

class Data
{
	private:
		std::vector<double> logl;
		std::vector<int> ids;

	public:
		Data();
		void load(const char* filename);

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

