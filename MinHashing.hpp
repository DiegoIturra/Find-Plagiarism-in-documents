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
		const unsigned numberOfHashFunctions = 20; //TODO: dejar en 100 o mas

		friend class LocalSensitiveHashing;

		vector<KShingleStructure> listOfKShinglesStructures;

		//map que guarda el nombre del documento junto a un id unico
		map<string,unsigned> idTable; 
		map<unsigned,string> idTableReverse;

		vector<vector<unsigned> > signatureMatrix;

		//Set que contiene todos los K-Shingles
		unordered_map<string,unsigned> mapOfAllKShingles;
		unordered_map<unsigned,string> mapOfAllKShinglesReverse;

		//Funciona que retorna un valor hash dado el idShingle, y una estructura
		//La cual contiene la tupla (a,b,p)
		unsigned hashFunction(unsigned idShingle,HashValues& hashValues);

		//Retorna un vector con los valores de la columna indicada
		vector<int> getColumnValues(unsigned column);

		//creacion de valores de las funciones hash
		vector<HashValues> createHashValues();

		//Metodo auxiliar para visualizar matriz caracteristica y de signatures
		void showCharacteristicMatrix();
		void showSignatureMatrix();

		//Verificar si existe un elemento en el set universal de shingles
		bool existShingle(const string& shingle);

		//Creat matriz de signatures
		void createSignatureMatrix();

		//crear un set con todo el universo de shingles
		void createMapOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures);

		//mapear todos los nombres de documentos con un id
		void mapFilenamesToIds(const vector<KShingleStructure>& listOfKShinglesStructures);

	public:
		MinHashing(vector<KShingleStructure>& listOfKShinglesStructures);

		void applyMinHash();
};

#endif