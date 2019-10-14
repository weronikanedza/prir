#include "FileLoader.hpp"
#include "Normalization.hpp"
#include "Standarization.hpp"
#include "KNN.hpp"
#include "omp.h"
#include <math.h>
#include <omp.h>
#include<iostream>
#include "KNNBeta.hpp"

using namespace std;

int main() {
	vector<Row> rows = FileLoader().readFile();
	Normalization normalization = Normalization(rows);
	Standarization standarization = Standarization(rows);


	//set threads num
	omp_set_num_threads(1);

	//normalization.normalize();
	//standarization.standarize();


	KNNBeta knnBeta = KNNBeta();
	knnBeta.knn(rows);

//	cout << "-------NORMALIZATION----------" << endl;
//	cout << "SUM : "
//			<< normalization.getMinMaxTime()
//					+ normalization.getNormalizationTime() << endl << endl;
//
//	cout << "========STANDARIZATION============" << endl;
//	cout << "SUM : "
//			<< standarization.getAverageCalcTime()
//					+ standarization.getDeviationTime()
//					+ standarization.getStandarizationTIme() << endl << endl;
//
//	cout << "********KNN*******" << endl;
//	cout << knn.getKnnTime() << endl;
//	cout << "Accuracy : " << knn.getAccuracy();
	return 0;
}

