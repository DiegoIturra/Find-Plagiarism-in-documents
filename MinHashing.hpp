#ifndef MINHASHING_HPP
#define MINHASHING_HPP

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "Commons.hpp"

using namespace std;

class MinHashing{
	private:
		map<string,unsigned> idTable; 

		vector<vector<unsigned> > characteristicMatrix;

		//Set que contiene todos los K-Shingles
		unordered_map<string,unsigned> mapOfAllKShingles;

		//Verificar si existe un elemento en el set universal de shingles
		bool existShingle(const string& shingle);

		//Crear matriz caracteristica con los shingles como filas y documentos como columnas
		void createCharacteristicMatrix(const vector<KShingleStructure>& listOfKShinglesStructures);

		//crear un set con todo el universo de shingles
		void createMapOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures);

		//mapear todos los nombres de documentos con un id
		void mapFilenamesToIds(const vector<KShingleStructure>& listOfKShinglesStructures);

	public:
		MinHashing(const vector<KShingleStructure>& listOfKShinglesStructures);
};

#endif