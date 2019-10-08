#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Row.hpp"

using namespace std;

#define NUM_OF_FEATURE 4

vector<Row> readFile();
Row loadRow(string line);

int main() {
	vector<Row> rows = readFile();
	return 0;
}

vector<Row> readFile() {

	ifstream file("iris.csv", ios::in);
	string line;
	vector<Row> rows;

	while (getline(file, line)) {
		rows.push_back(loadRow(line));
	}


	file.close();
	return rows;
}

Row loadRow(string line) {
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
