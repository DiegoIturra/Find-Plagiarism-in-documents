#ifndef MINHASHING_HPP
#define MINHASHING_HPP

#include <unordered_map>

using namespace std;

class MinHashing{
	private:
		int hashing;
		unordered_map<string,unsigned> idTable; 

	public:
		MinHashing();
};

#endif