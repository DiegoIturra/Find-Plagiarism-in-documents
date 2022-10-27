#ifndef UTILS_FUNCTIONS
#define UTILS_FUNCTIONS

#include <vector>

using namespace std;

int nextPrime(const int number);
template <typename T,typename V> bool exist(T& collection,V& element);
vector<unsigned> generateRandomNumbers(unsigned k,unsigned upperBoundLimit);

#endif