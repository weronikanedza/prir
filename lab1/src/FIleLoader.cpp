#include "FileLoader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

vector<Row> FileLoader::readFile() {

	ifstream file("krkopt.csv", ios::in);
	string line;
	vector<Row> rows;

	while (getline(file, line)) {
		rows.push_back(loadRow(line));
	}

	file.close();
	return rows;
}

Row FileLoader::loadRow(string line) {
	vector<double> features;
	string word;
	stringstream s(line);

	for (int i = 0; i < NUM_OF_FEATURES; i++) {
		getline(s, word, ',');
		string preparedWord = prepareData(word);
		features.push_back(atof(preparedWord.c_str()));
	}

	getline(s, word, ',');
	return Row(features, word);

}

string FileLoader::prepareData(string word) {


	if(word.compare("a")==0){
		return "1";
	}else if(word.compare("b")==0){
		return "2";
	}else if(word.compare("c")==0){
		return "3";
	}else if(word.compare("d")==0){
		return "4";
	}else if(word.compare("e")==0){
		return "5";
	}else if(word.compare("f")==0){
		return "6";
	}else if(word.compare("g")==0){
		return "7";
	}else if(word.compare("h")==0){
		return "8";
	}

//	if (word.compare("M")==0) {
//		return "1";
//	} else if (word.compare("F")==0) {
//		return "2";
//	} else if (word.compare("I")==0) {
//		return "3";
//	}

	return word;
}
