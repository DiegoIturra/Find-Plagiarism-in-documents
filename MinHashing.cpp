#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <unordered_set>
#include <unordered_map>
#include "Commons.hpp"
#include "UtilsFunctions.hpp"
#include "MinHashing.hpp"

using namespace std;

/********************* Metodos de testeo **********************/
void MinHashing::showSignatureMatrix(){
	cout << "Signature Matrix " << endl;
	for(int i=0 ; i<signatureMatrix.size() ; i++){
		for(int j=0 ; j<signatureMatrix[i].size() ; j++){
			cout << signatureMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
/********************* Fin Metodos de testeo **********************/


bool MinHashing::existShingle(const string& shingle){
	auto mapIterator = this->mapOfAllKShingles.find(shingle);
	if(mapIterator == this->mapOfAllKShingles.end())
		return false;
	return true;
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
		this->idTableReverse[uniqueId] = filename;
		uniqueId++; 
	}
}


//Crear un set universal con todos los shingles existentes
void MinHashing::createMapOfShingles(const vector<KShingleStructure>& listOfKShinglesStructures){
	unsigned uniqueId = 0;
	for(KShingleStructure kshingleStructure : listOfKShinglesStructures){
		for(auto kshingle : kshingleStructure.listOfKShingles){
			//TODO: reemplazar funcion existShingle por funcion template
			if(!existShingle(kshingle)){
				this->mapOfAllKShingles[kshingle] = uniqueId;
				this->mapOfAllKShinglesReverse[uniqueId] = kshingle;
				uniqueId++;
			}
		}
	}
}


//crear las estructuras basicas necesarias para poder usar algoritmo de MinHashing
MinHashing::MinHashing(vector<KShingleStructure>& listOfKShinglesStructures){
	//Guardamos la referencia de la lista de kshingleStructure
	this->listOfKShinglesStructures = listOfKShinglesStructures;

	//Asignamos un ID a cada shingle unico
	createMapOfShingles(listOfKShinglesStructures);

	//Asignamos un ID a cada documento
	mapFilenamesToIds(listOfKShinglesStructures);

	//TODO: Reestructurar y no usar matriz caracteristica
	//createCharacteristicMatrix(listOfKShinglesStructures);

	//Eliminar lista con documento y sus shinghles. No es necesario mantener en memoria
	//listOfKShinglesStructures.clear(); 
	srand(time(NULL));
}



//Crear un vector con los valores (a,b,p) de cada funcion hash
vector<HashValues> MinHashing::createHashValues(){
	unsigned maxRows = this->mapOfAllKShingles.size();
	unsigned nextPrimeNumber = nextPrime(maxRows);

	vector<unsigned> randomNumbersA = generateRandomNumbers(maxRows,nextPrimeNumber);
	vector<unsigned> randomNumbersB = generateRandomNumbers(maxRows,nextPrimeNumber);
	vector<HashValues> vectorOfHashValues;

	for(int i=0 ; i<this->numberOfHashFunctions ; i++){
		HashValues hashValue;
		hashValue.a = randomNumbersA[i];
		hashValue.b = randomNumbersB[i];
		hashValue.p = nextPrimeNumber;

		vectorOfHashValues.push_back(hashValue);
	}

	return vectorOfHashValues;
}



//Retorna un hash para el id del shingle dado
unsigned MinHashing::hashFunction(unsigned idShingle , HashValues& hashValues){
	return (hashValues.a * idShingle + hashValues.b) % hashValues.p;
}



void MinHashing::applyMinHash(){
	
	//Vector que contiene k valores de los parametros de funcion hash (a,b,p)
	vector<HashValues> vectorOfHashValues = createHashValues();

	//Por cada documento existente
	for(KShingleStructure kshingleStructure : this->listOfKShinglesStructures){
		vector<unsigned> signature;
		//Por cada funcion hash existente
		for(int hashNumber=0 ; hashNumber<numberOfHashFunctions ; hashNumber++){
			unsigned minVal = 999999999;
			//Para cada shingle en el documento actual
			for(string shingle : kshingleStructure.listOfKShingles){
				unsigned idShingle = mapOfAllKShingles[shingle];
				minVal = min(minVal,hashFunction(idShingle,vectorOfHashValues[hashNumber]));
			}
			signature.push_back(minVal);
		}

		this->signatureMatrix.push_back(signature);
	}

	showSignatureMatrix();
}