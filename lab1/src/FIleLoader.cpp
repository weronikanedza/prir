#include "FileLoader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#define NUM_OF_FEATURE 4

vector<Row> FileLoader::readFile() {

	ifstream file("iris.csv", ios::in);
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

	for (int i = 0; i < NUM_OF_FEATURE; i++) {
		getline(s, word, ',');
		features.push_back(atof(word.c_str()));
	}
	getline(s, word, ',');

	return Row(features, word);
}
