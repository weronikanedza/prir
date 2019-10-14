#include "KNN.hpp"
#include "math.h"
#include<map>
#include<algorithm>
#include<random>
#include "omp.h"
#include<iostream>

using namespace std;

void KNN::createSets() {

	auto randomEngine = default_random_engine { };
	shuffle(begin(inData), end(inData), randomEngine);
	int trainingSetSplit = 0.7 * inDataSize;

	for (int i = 0; i < trainingSetSplit; i++) {
		trainingSet.push_back(inData[i]);
	}

	for (int i = trainingSetSplit; i < inDataSize; i++) {
		testingSet.push_back(inData[i]);
	}
}

void KNN::knn() {
	//number of neighbours
	int K = 3;

	priority_queue<Row, vector<Row>, CompareRows> neighbours;

	int testingSetSize = testingSet.size();
	int i;
	string prediction;

	double begin = omp_get_wtime();

#pragma omp parallel for default(none) shared(testingSetSize,testingSet,neighbours,K) private(i,prediction)
	for (i = 0; i < testingSetSize; i++) {
		prediction = calculatePrediction(neighbours, testingSet[i], K);
		testingSet[i].prediction = prediction;
	}

	double end = omp_get_wtime();
	knnTime = end - begin;
}

double KNN::getAccuracy() {

	int correct = 0;
	int i;
	int testingSetSize = testingSet.size();

#pragma omp parallel for default(none) shared(testingSetSize,testingSet) private(i) reduction(+:correct)
	for (i = 0; i < testingSetSize; i++) {
		if (testingSet[i].prediction.compare(testingSet[i].category) == 0) {
			correct += 1;
		}
	}

	return correct / (double) testingSet.size() * 100.0;
}

string KNN::calculatePrediction(
		priority_queue<Row, vector<Row>, CompareRows> neighbours,
		Row testingVal, int K) {
	int trainingSetSize = trainingSet.size();
	int j;

 #pragma omp parallel for default(none) shared(trainingSetSize,testingVal,trainingSet,neighbours ) private(j)
	for (j = 0; j < trainingSetSize; j++) {
		double dist = calculateEuclideanDist(testingVal, trainingSet[j]);
		trainingSet[j].distance = dist;
		neighbours.push(trainingSet[j]);
	}

	return votePrediction(neighbours, K);
}

string KNN::votePrediction(
		priority_queue<Row, vector<Row>, CompareRows> neighbours, int K) {

	map<string, int> votes;


#pragma omp parallel
	{
	//one local vector for each thread
	auto tempNeighbours = neighbours;

   #pragma omp for
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
}



	string maxVotesCategory = "draw";
	int votesNumber = 0;
	map<string, int>::iterator it;
	auto endVotes = votes.end();
	auto startVotes = votes.begin();

	for (it = startVotes; it != endVotes; it++) {

		if (votesNumber < it->second) {
			votesNumber = it->second;
			maxVotesCategory = it->first;
		}
	}

	return maxVotesCategory;
}

double KNN::calculateEuclideanDist(Row testingRow, Row trainingRow) {
	double dist = 0;
	int num_of_feaqtures = NUM_OF_FEATURES;
	int k;

	#pragma omp parallel for default(none) shared(testingRow,trainingRow,num_of_feaqtures) private (k) reduction(+:dist)
	for (k = 0; k < num_of_feaqtures; k++) {
		dist += pow(testingRow.features[k] - trainingRow.features[k], 2);
	}

	return dist;
}

double KNN::getKnnTime() {
	return knnTime;
}

vector<Row> KNN::getTestSet(){
	return testingSet;
}

vector<Row> KNN::getTrainSet(){
	return trainingSet;
}
