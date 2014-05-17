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

		const std::vector<double>& get_logl() const { return logl; }
		const std::vector<int>& get_ids() const { return ids; }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

