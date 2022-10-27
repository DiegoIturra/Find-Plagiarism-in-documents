#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

struct KShingleStructure{
	string filename;
	unordered_set<string> listOfKShingles;
};

struct FileStructure{
	string filename;
	string text;
};

struct HashValues{
	unsigned a;
	unsigned b;
	unsigned p;
};


#endif