#include "FileLoader.hpp"
#include "Normalization.hpp"
#include "Standarization.hpp"
#include "omp.h"
#include <math.h>
#include <omp.h>
#include <iostream>

#include "KNN.hpp"

using namespace std;

int main() {
	vector<Row> rows = FileLoader().readFile();
	Normalization normalization = Normalization(rows);
	Standarization standarization = Standarization(rows);
	KNN knn = KNN();

	//set threads num
	omp_set_num_threads(2);

	normalization.normalize();
	standarization.standarize();
	knn.knn(rows);

	cout << "-------NORMALIZATION----------" << endl;
	cout << "SUM : "
			<< normalization.getMinMaxTime()
					+ normalization.getNormalizationTime() << endl << endl;

	cout << "========STANDARIZATION============" << endl;
	cout << "SUM : "
			<< standarization.getAverageCalcTime()
					+ standarization.getDeviationTime()
					+ standarization.getStandarizationTIme() << endl << endl;

	cout<<"********KNN**************"<<endl;
	cout << "ACC : " << knn.accuracy<< endl;
	cout << "TIME : " << knn.knnTime << endl<<endl;

	return 0;
}

