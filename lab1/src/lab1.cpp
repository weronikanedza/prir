#include "FileLoader.hpp"
#include "Normalization.hpp"
#include "Standarization.hpp"
#include "KNN.hpp"

#include <math.h>
#include <omp.h>
#include<iostream>
using namespace std;

int main() {
	vector<Row> rows = FileLoader().readFile();
	Normalization normalization = Normalization(rows);
	Standarization standarization = Standarization(rows);
	KNN knn = KNN(rows);

	//normalization.normalize();
	//standarization.standarize();
	knn.createSets();
	knn.knn();
	cout << knn.getAccuracy();
	return 0;
}

