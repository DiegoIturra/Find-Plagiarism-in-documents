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
void MinHashing::showCharacteristicMatrix(){
	cout << "Characteristic Matrix" << endl;
	for(int i=0 ; i<characteristicMatrix.size() ; i++){
		cout << this->mapOfAllKShinglesReverse[i] << " ";
		for(int j=0 ; j<characteristicMatrix[i].size() ; j++){
			cout << characteristicMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

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


void MinHashing::createCharacteristicMatrix(const vector<KShingleStructure>& listOfKShinglesStructures){
	//Idea: crear una matriz con numero de filas igual al numero de shingles unicos
	unsigned totalRows = this->mapOfAllKShingles.size();
	unsigned totalColumns = listOfKShinglesStructures.size();
	characteristicMatrix.resize(totalRows,vector<unsigned>(totalColumns));


	//Para ello necesito mapear el nombre del documento actual a procesar y obtener su id
	unsigned row,column;
	for(KShingleStructure kshingleStructure : listOfKShinglesStructures){
		column = idTable[kshingleStructure.filename]; //Entrega la columna del documento

		for(string shingle : kshingleStructure.listOfKShingles){
			row = mapOfAllKShingles[shingle]; //Obtener la fila que representa un elemento del set de shingles
			characteristicMatrix[row][column] = 1;
		}
	}
}


void MinHashing::createSignatureMatrix(){
	unsigned numColumns = characteristicMatrix[0].size();
	signatureMatrix.resize(numberOfHashFunctions,vector<unsigned>(numColumns,9999999));
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
	createMapOfShingles(listOfKShinglesStructures);
	mapFilenamesToIds(listOfKShinglesStructures);
	createCharacteristicMatrix(listOfKShinglesStructures);
	listOfKShinglesStructures.clear(); //No es necesario mantener en memoria
	srand(time(NULL));

	//Impresion de prueba (documento,id)
	/*for(auto& [filename,uniqueId] : this->idTable){
		cout << filename << " -> " << uniqueId << endl;
	}
	cout << endl;
	*/

	//(shingle,numero_fila)
	for(auto& [kshingle,id] : this->mapOfAllKShingles){
		cout << kshingle << " -> " << id << endl;
	}

	
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



vector<int> MinHashing::getColumnValues(unsigned column){
	vector<int> columnValues;
	for(int row=0; row<characteristicMatrix.size() ; row++){
		columnValues.push_back(characteristicMatrix[row][column]);
	}
	return columnValues;
}


void MinHashing::applyMinHash(){
	
	//Vector que contiene k valores de los parametros de funcion hash (a,b,p)
	vector<HashValues> vectorOfHashValues = createHashValues();

	int module = vectorOfHashValues[0].p;
	unsigned numColumns = characteristicMatrix[0].size(); //Asumimos que tenemos algun valor

	//Inicializar matriz de signatures
	createSignatureMatrix();

	for(int column=0 ; column<numColumns ; column++){
		vector<int> document = getColumnValues(column);

		for(int i=0 ; i<numberOfHashFunctions; i++){
			unsigned minHash = module + 1;
			unsigned idShingle = 0;

			for(int k : document){
				if(k == 1){
					unsigned hash = hashFunction(idShingle,vectorOfHashValues[i]);
					minHash = min(hash,minHash);
				}
				idShingle++;
			}
			signatureMatrix[i][column] = minHash;
		}
	}

	//showCharacteristicMatrix();
	//showSignatureMatrix();
}