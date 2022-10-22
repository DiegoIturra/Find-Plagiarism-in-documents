#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <unordered_set>

using namespace std;

struct KShingleStructure{
	string filename;
	unordered_set<string> listOfKShingles;
};

struct FileStructure{
	string filename;
	string text;
};

#endif