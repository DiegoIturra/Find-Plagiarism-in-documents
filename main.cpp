#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

struct FileStructure{
	string filename;
	string text;
};

//Retorna el texto parseado (READY)
string parseText(const string& path){
	ifstream file;
	string text;
	string completeText;

	file.open(path);
	if(file.is_open()){
		while(file.good()){
			file >> text;
			completeText += text;
		}
	}

	return completeText;
}

void writeNewDocument(const FileStructure& fileStructure){
	const string newPathFolder = "/Users/diego/Desktop/proyectoTopicos/preprocessing_corpus/";

	ofstream outputText(newPathFolder + fileStructure.filename,ofstream::out);

	outputText << fileStructure.text;
}


void saveDocumentsIntoNewFolder(const vector<FileStructure> listOfParsedDocuments){
	for(FileStructure fileStructure : listOfParsedDocuments){
		writeNewDocument(fileStructure);
	}
}


//Parsea los documentos y retorna una lista con <filename,text>
vector<FileStructure> getSetOfParsedDocuments(const vector<string>& listOfFileNames){
	const string orignalPathFolder = "/Users/diego/Desktop/proyectoTopicos/original_corpus/";

	vector<FileStructure> listOfParsedDocuments;
	FileStructure fileStructure;
	for(string filename : listOfFileNames){
		fileStructure.filename = filename;
		fileStructure.text = parseText(orignalPathFolder+filename);
		listOfParsedDocuments.push_back(fileStructure);
	}
	return listOfParsedDocuments;
}



//Retorna una lista con los nombres de los ficheros originales (READY)
vector<string> getFilenamesFromOriginalCorpus(){
	const string path = "/Users/diego/Desktop/proyectoTopicos/original_corpus";

	vector<string> listOfFileNames;
	for(const auto& entry : filesystem::directory_iterator(path)){
		listOfFileNames.push_back(entry.path().filename());
	}

	return listOfFileNames;
}

int main(){
	
	//Obtener lista de nombres de los documentos
	vector<string> listOfFileNames = getFilenamesFromOriginalCorpus();

	//Obtener textos parseados
	vector<FileStructure> listOfParsedDocuments = getSetOfParsedDocuments(listOfFileNames);

	//Guardar textos parseados en una nueva carpeta con ficheros preprocesados
	saveDocumentsIntoNewFolder(listOfParsedDocuments);

	return 0;
}
