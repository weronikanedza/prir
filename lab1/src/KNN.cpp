#include "KNN.hpp"
#include "math.h"
#include<map>

void KNN::createSets() {
	//3 categories each 50 rows
	int teachingSetSize = 0.6 * inData.size() / 3;

	for (int i = 0; i < 3; i++) {
		for (int j = i * 50; j < i * 50 + teachingSetSize; j++) {
			trainingSet.push_back(inData[j]);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = i * 50 + teachingSetSize; j < i * 50 + 50; j++) {
			testingSet.push_back(inData[j]);
		}
	}

}

void KNN::knn() {
	//number of neighbours
	int K = 3;

	priority_queue<Row, vector<Row>, CompareRows> neighbours;

	for (int i = 0; i < testingSet.size(); i++) {
		int prediction = calculatePrediction(neighbours, testingSet[i], K);
		testingSet[i].prediction = prediction;
	}

}

double KNN::getAccuracy() {
	int correct = 0;
	for (int i = 0; i < testingSet.size(); i++) {

		if (testingSet[i].prediction == testingSet[i].category) {
			correct += 1;
		}
	}

	return correct / (double) testingSet.size() * 100.0;
}

int KNN::calculatePrediction(
		priority_queue<Row, vector<Row>, CompareRows> neighbours,
		Row testingVal, int K) {

	for (int j = 0; j < trainingSet.size(); j++) {
		double dist = calculateEuclideanDist(testingVal, trainingSet[j]);
		trainingSet[j].distance = dist;
		neighbours.push(trainingSet[j]);
	}

	return votePrediction(neighbours, K);
}

int KNN::votePrediction(
		priority_queue<Row, vector<Row>, CompareRows> neighbours, int K) {

	map<int, int> votes;

	for (int i = 0; i < K; i++) {
		int category = neighbours.top().category;
		neighbours.pop();
		map<int, int>::iterator iterator = votes.find(category);

		if (iterator == votes.end()) {
			votes[category]= 1;
		} else {
			int v = votes.at(category);
			votes[category]= ++v;
		}
	}

	int maxVotesCategory = 0;
	int votesNumber = 0;
	map<int, int>::iterator it;

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
