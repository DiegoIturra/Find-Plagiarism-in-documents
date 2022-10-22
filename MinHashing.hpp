#ifndef MINHASHING_HPP
#define MINHASHING_HPP

#include <vector>
#include <unordered_set>
#include <map>
#include "Commons.hpp"

using namespace std;

class MinHashing{
	private:
		map<string,unsigned> idTable; 

		vector<vector<unsigned long long> > characteristicMatrix;

		//Set que contiene todos los K-Shingles
		unordered_set<string> setOfAllKShingles;

		//crear un set con todo el universo de shingles
		void createSetOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures);

		//mapear todos los nombres de documentos con un id
		void mapFilenamesToIds(const vector<KShingleStructure>& listOfKShinglesStructures);

	public:
		MinHashing(const vector<KShingleStructure>& listOfKShinglesStructures);
};

#endif