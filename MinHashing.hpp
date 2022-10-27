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
		const unsigned numberOfHashFunctions = 100;

		//map que guarda el nombre del documento junto a un id unico
		map<string,unsigned> idTable; 

		vector<vector<unsigned> > characteristicMatrix;

		vector<vector<unsigned> > signatureMatrix;

		//Set que contiene todos los K-Shingles
		unordered_map<string,unsigned> mapOfAllKShingles;

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

		//Crear matriz caracteristica con los shingles como filas y documentos como columnas
		void createCharacteristicMatrix(const vector<KShingleStructure>& listOfKShinglesStructures);

		//Creat matriz de signatures
		void createSignatureMatrix();

		//crear un set con todo el universo de shingles
		void createMapOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures);

		//mapear todos los nombres de documentos con un id
		void mapFilenamesToIds(const vector<KShingleStructure>& listOfKShinglesStructures);

	public:
		MinHashing(const vector<KShingleStructure>& listOfKShinglesStructures);

		void applyMinHash();
};

#endif