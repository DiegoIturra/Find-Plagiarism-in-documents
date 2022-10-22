#include <algorithm>
#include <iostream>
#include <vector>
#include "Commons.hpp"
#include "MinHashing.hpp"

using namespace std;

void MinHashing::mapFilenamesToIds(const vector<KShingleStructure>& listOfKShinglesStructures){
	vector<string> listOfFilenames;

	for(KShingleStructure kshingleStructure : listOfKShinglesStructures){
		listOfFilenames.push_back(kshingleStructure.filename);
	}

	sort(listOfFilenames.begin(),listOfFilenames.end());

	unsigned uniqueId = 0;
	for(string filename : listOfFilenames){
		this->idTable[filename] = uniqueId;
		uniqueId++; 
	}
}


void MinHashing::createSetOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures){
	for(KShingleStructure kshingleStructure : listOfKShinglesStructures){
		for(auto kshingle : kshingleStructure.listOfKShingles){
			this->setOfAllKShingles.insert(kshingle);
		}
	}
}


MinHashing::MinHashing(const vector<KShingleStructure>& listOfKShinglesStructures){
	createSetOfShingles(listOfKShinglesStructures);
	mapFilenamesToIds(listOfKShinglesStructures);

	//Impresion de prueba
	for(auto& [filename,uniqueId] : this->idTable){
		cout << filename << " -> " << uniqueId << endl;
	}

}