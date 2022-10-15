#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

void parseText(const string& path){

}

vector<string> getPathFromOriginalCorpus(){
	const string path = "/Users/diego/Desktop/proyectoTopicos/original_corpus";

	vector<string> listOfPathFiles;
	for(const auto& entry : filesystem::directory_iterator(path)){
		listOfPathFiles.push_back(entry.path());
	}

	return listOfPathFiles;
}

int main(){
	
	getPathFromOriginalCorpus();

	return 0;
}

	/*ifstream file;
	string text;
	int counter = 0;
	for(const auto& entry : filesystem::directory_iterator(path)){

		if(counter > 0) break;
		file.open(entry.path());
		cout << entry.path() << endl;

		if(file.is_open()){
			while(file.good()){
				file >> text;
				cout << text;
			}
		}

		counter++;
	}*/