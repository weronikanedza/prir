#include "KNN.hpp"
#include "math.h"
#include<map>
#include<algorithm>
#include<random>

void KNN::createSets() {
	//3 categories each 50 rows
	auto randomEngine = default_random_engine { };
	shuffle(begin(inData), end(inData), randomEngine);
	int trainingSetSplit = 0.8 * inDataSize;

	for (int i = 0; i < trainingSetSplit; i++) {
		trainingSet.push_back(inData[i]);
	}

	for (int i = trainingSetSplit; i < inDataSize; i++) {
		testingSet.push_back(inData[i]);
	}
}

void KNN::knn() {
	//number of neighbours
	int K = 1;

	priority_queue<Row, vector<Row>, CompareRows> neighbours;

	int testingSetSize = testingSet.size();
	int i;

//	#pragma omp parallel for default(none) shared(testingSize,testingSet,neighbours) private(i)

	for (i = 0; i < testingSetSize; i++) {
		string prediction = calculatePrediction(neighbours, testingSet[i], K);
		testingSet[i].prediction = prediction;
	}

}

double KNN::getAccuracy() {
	int correct = 0;
	for (int i = 0; i < testingSet.size(); i++) {

		if (testingSet[i].prediction.compare(testingSet[i].category) == 0) {
			correct += 1;
		}
	}

	return correct / (double) testingSet.size() * 100.0;
}

string KNN::calculatePrediction(
		priority_queue<Row, vector<Row>, CompareRows> neighbours,
		Row testingVal, int K) {

	for (int j = 0; j < trainingSet.size(); j++) {
		double dist = calculateEuclideanDist(testingVal, trainingSet[j]);
		trainingSet[j].distance = dist;
		neighbours.push(trainingSet[j]);
	}

	return votePrediction(neighbours, K);
}

string KNN::votePrediction(
		priority_queue<Row, vector<Row>, CompareRows> neighbours, int K) {

	map<string, int> votes;

	for (int i = 0; i < K; i++) {
		string category = neighbours.top().category;
		neighbours.pop();
		map<string, int>::iterator iterator = votes.find(category);

		if (iterator == votes.end()) {
			votes[category] = 1;
		} else {
			int v = votes.at(category);
			votes[category] = ++v;
		}
	}

	string maxVotesCategory = "Iris-setosa";
	int votesNumber = 0;
	map<string, int>::iterator it;

	for (it = votes.begin(); it != votes.end(); it++) {
		if (votesNumber < it->second) {
			votesNumber = it->second;
			maxVotesCategory = it->first;
		}
	}

	return maxVotesCategory;
}

double KNN::calculateEuclideanDist(Row testingRow, Row trainingRow) {
	double dist;

	for (int k = 0; k < NUM_OF_FEATURES; k++) {
		dist += pow(testingRow.features[k] - trainingRow.features[k], 2);
	}

	return dist;
}
