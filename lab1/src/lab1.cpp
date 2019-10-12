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

	normalization.normalize();
	standarization.standarize();
	knn.createSets();
	knn.knn();

	cout << "-------NORMALIZATION----------" << endl;
	cout << "Min max alg time : " << normalization.getMinMaxTime() << endl;
	cout << "Normalzation time : " << normalization.getNormalizationTime()
			<< endl;
	cout << "SUM : "
			<< normalization.getMinMaxTime()
					+ normalization.getNormalizationTime() << endl << endl;

	cout << "========STANDARIZATION============" << endl;
	cout << "Average calc time : " << standarization.getAverageCalcTime()
			<< endl;
	cout << "Deviation calc time : " << standarization.getDeviationTime()
			<< endl;
	cout << "Standarization calc time : "
			<< standarization.getStandarizationTIme() << endl;
	cout << "SUM : "
			<< standarization.getAverageCalcTime()
					+ standarization.getDeviationTime()
					+ standarization.getStandarizationTIme() << endl << endl;

	cout << "Accuracy : " << knn.getAccuracy();
	return 0;
}

