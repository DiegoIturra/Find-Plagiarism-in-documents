#include <algorithm>
#include <iostream>
#include <vector>
#include "Commons.hpp"
#include "MinHashing.hpp"

using namespace std;

bool MinHashing::existShingle(const string& shingle){
	auto mapIterator = this->mapOfAllKShingles.find(shingle);
	if(mapIterator == this->mapOfAllKShingles.end())
		return false;
	return true;
}


void MinHashing::createCharacteristicMatrix(const vector<KShingleStructure>& listOfKShinglesStructures){
	//Idea: crear una matriz con numero de filas igual al numero de shingles unicos
	unsigned totalRows = this->mapOfAllKShingles.size();
	characteristicMatrix.resize(totalRows,vector<unsigned>(listOfKShinglesStructures.size()));

	cout << "Total rows: " << totalRows << endl;

	//Iterar sobre todos los documentos y poder marcar con 1 si el shingle existe en ese documento
	//o con 0 si el shingle no existe en ese documento

	//Para ello necesito mapear el nombre del documento actual a procesar y obtener su id
	unsigned row,column;
	for(KShingleStructure kshingleStructure : listOfKShinglesStructures){
		column = idTable[kshingleStructure.filename]; //Entrega la columna del documento

		for(string shingle : kshingleStructure.listOfKShingles){
			row = mapOfAllKShingles[shingle]; //Obtener la fila que representa un elemento del set de shingles
			characteristicMatrix[row][column] = 1;
		}
	}

	for(int i=0 ; i<characteristicMatrix.size() ; i++){
		for(int j=0 ; j<characteristicMatrix[i].size() ; j++){
			cout << characteristicMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}

//Mapear los nombres de los documentos a un Id unico
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


//Crear un set universal con todos los shingles existentes
void MinHashing::createMapOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures){
	unsigned uniqueId = 0;
	for(KShingleStructure kshingleStructure : listOfKShinglesStructures){
		for(auto kshingle : kshingleStructure.listOfKShingles){
			if(!existShingle(kshingle)){
				this->mapOfAllKShingles[kshingle] = uniqueId;
				uniqueId++;
			}
		}
	}
}


//crear las estructuras basicas necesarias para poder usar algoritmo de MinHashing
MinHashing::MinHashing(const vector<KShingleStructure>& listOfKShinglesStructures){
	createMapOfShingles(listOfKShinglesStructures);
	mapFilenamesToIds(listOfKShinglesStructures);

	//Impresion de prueba
	
	for(auto& [filename,uniqueId] : this->idTable){
		cout << filename << " -> " << uniqueId << endl;
	}
	cout << endl;

	createCharacteristicMatrix(listOfKShinglesStructures);

	/*for(auto& [kshingle,id] : this->mapOfAllKShingles){
		cout << kshingle << " -> " << id << endl;
	}*/

}