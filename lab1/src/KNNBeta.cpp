#include "KNNBeta.hpp"
#include "math.h"
#include <iostream>
#include "omp.h"
#include<algorithm>
#include<random>
#include<queue>

#define CATEGORY_NUM 18

using namespace std;
void KNNBeta::knn(vector<Row> rows) {

	int i;
	int K = 3;

	splitData(rows);

	double begin = omp_get_wtime();
	for (i = 0; i < testSize; i++) {
		int prediction = calcPrediction(testSet[i], K);
		testSet[i].prediction = prediction;
	}

	int correct = 0;

#pragma omp parallel for default(none) shared(testSet,testSize) private(i) reduction(+:correct)
	for (i = 0; i < testSize; i++) {
		if (testSet[i].prediction == testSet[i].category) {
			correct += 1;
		}
	}
	double end = omp_get_wtime();

	cout<< "************KNN***********" <<endl;
	cout << "ACC : " << correct / (double) testSize * 100.0 << endl;
	cout << "TIME : " << end - begin << endl;
}

int KNNBeta::calcPrediction(Test testVal, int K) {
	int j;

	priority_queue<Test, vector<Test>, CompareTest> neighbours;

#pragma omp parallel for default(none) shared(trainSize,testVal,neighbours) private(j)
	for (j = 0; j < trainSize; j++) {
		double dist = calcDist(testVal, trainSet[j]);
		trainSet[j].distance = dist;
		neighbours.push(trainSet[j]);
	}

	int votes[CATEGORY_NUM] = { };

	for (int i = 0; i < K; i++) {
		int voteCategory = neighbours.top().category;
		neighbours.pop();
		votes[voteCategory] += 1;
	}

	int maxVotes = 0;
	int category = 0;
	for (int i = 0; i < CATEGORY_NUM; i++) {
		if (votes[i] > maxVotes) {
			maxVotes = votes[i];
			category = i;
		}
	}

	return category;
}

double KNNBeta::calcDist(Test test, Test train) {
	double dist = 0;
	int num_of_feaqtures = NUM_OF_FEATURES;
	int k;

	for (k = 0; k < num_of_feaqtures; k++) {
		dist += pow(test.features[k] - train.features[k], 2);
	}

	return dist;
}

void KNNBeta::splitData(vector<Row> inData) {

	auto randomEngine = default_random_engine { };
	shuffle(begin(inData), end(inData), randomEngine);
	trainSize = 0.7 * inData.size();
	testSize = inData.size() - trainSize;

	for (int i = 0; i < trainSize; i++) {
		Test t = Test();
		t.category = inData[i].category;
		for (int j = 0; j < NUM_OF_FEATURES; j++) {
			t.features[j] = inData[i].features[j];
		}

		trainSet.push_back(t);
	}

	for (int i = trainSize; i < inData.size(); i++) {
		Test t;
		t.category = inData[i].category;
		for (int j = 0; j < NUM_OF_FEATURES; j++) {
			t.features[j] = inData[i].features[j];
		}
		testSet.push_back(t);
	}

}
