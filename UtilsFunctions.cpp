#include "UtilsFunctions.hpp"
#include <unordered_set>
#include <vector>
#include <random>

using namespace std;


//Obtener un numero primo mayor al numero de shingles totales
int nextPrime(const int number){
	if (number <= 1)
		return 2;
		
	int prime = number;
	bool found = false;

	//Lambda function
	auto isPrime = [](int number){
		for (int i = 2; i <= sqrt(number); i++)
			if (number % i == 0)
				return false;
		return true;
	};
		
	//Iterar hasta que se encuentre el numero primo mayor a N
	while (!found) {
		prime++;
		if(isPrime(prime))
			found = true;
	}
	return prime;
}


/*bool exist(unordered_set<unsigned>& setOfRandomNumbers,unsigned randomNumber){
	auto setIterator = setOfRandomNumbers.find(randomNumber);
	if(setIterator == setOfRandomNumbers.end())
		return false;
	return true;
}*/


template <typename T,typename V>
bool exist(T& collection , V& element){
	auto iterator = collection.find(element);
	if(iterator == collection.end())
		return false;
	return true;
}


vector<unsigned> generateRandomNumbers(unsigned k,unsigned upperBoundLimit){
	vector<unsigned> randomNumbers;
	unordered_set<unsigned> setOfRandomNumbers;

	while(k > 0){
		unsigned randomNumber = rand() % upperBoundLimit;

		while(exist<unordered_set<unsigned>& , unsigned&>(setOfRandomNumbers,randomNumber)){
			randomNumber = rand() % upperBoundLimit;
		}
		
		k--;
		setOfRandomNumbers.insert(randomNumber);
		randomNumbers.push_back(randomNumber);
	}

	return randomNumbers;
}