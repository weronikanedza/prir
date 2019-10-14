#include "KNNBeta.hpp"
#include "math.h"
#include <iostream>
#include "omp.h"
#include<algorithm>
#include<random>

using namespace std;
void KNNBeta::knn(vector<Row> rows) {

	int i;
	int K = 3;

	splitData(rows);

	double begin = omp_get_wtime();
	for (i = 0; i < testSize; i++) {
		string prediction = calcPrediction(test[i], 3);
		test[i].prediction = prediction;
	}

	int correct = 0;



	//#pragma omp parallel for default(none) shared(testingSetSize,testingSet) private(i) reduction(+:correct)
	for (i = 0; i < testSize; i++) {
		if (test[i].prediction.compare(test[i].category) == 0) {
			correct += 1;
		}
	}
	double end = omp_get_wtime();

	cout << "ACC : " << correct / (double) testSize * 100.0<<endl;
	cout << "TIME : " << end - begin << endl;
}

string KNNBeta::calcPrediction(Test testVal, int K) {
	int j;
	double min = 1000000;
	Test neigbour;

	for (j = 0; j < trainSize; j++) {

		double dist = calcDist(testVal, train[j]);
		train[j].distance = dist;
		if (min > dist) {
			min = dist;
			neigbour = train[j];
		}
	}

	return neigbour.category;
}

double KNNBeta::calcDist(Test test, Test train) {
	double dist = 0;
	int num_of_feaqtures = NUM_OF_FEATURES;
	int k;

	//#pragma omp parallel for default(none) shared(testingRow,trainingRow,num_of_feaqtures) private (k) reduction(+:dist)
	for (k = 0; k < num_of_feaqtures; k++) {
		dist += pow(test.features[k] - train.features[k], 2);
	}

	return dist;
}

void KNNBeta::splitData(vector<Row> inData) {

	auto randomEngine = default_random_engine { };
	shuffle(begin(inData), end(inData), randomEngine);
	trainSize =  0.7 * inData.size();
	testSize = inData.size() - trainSize;
	test = new Test[testSize];
	train = new Test[trainSize];

	for (int i = 0; i < trainSize; i++) {
		train[i].category = inData[i].category;
		for (int j = 0; j < NUM_OF_FEATURES; j++) {
			train[i].features[j] = inData[i].features[j];
		}
	}

	int k = trainSize;
	for (int i = 0; i < testSize; i++) {
		test[i].category = inData[k].category;

		for (int j = 0; j < NUM_OF_FEATURES; j++) {
			test[i].features[j] = inData[k].features[j];
		}
		++k;
	}


}
