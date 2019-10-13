#include "Normalization.hpp"
#include<limits>

void Normalization::normalize() {
	findMinMax();

	int num_of_features = NUM_OF_FEATURES;
	int i, j;
	double begin = omp_get_wtime();

	#pragma omp parallel for default(none) shared(inData,inDataSize,num_of_features,min,max) private(i,j)
	for (i = 0; i < inDataSize; i++) {
		for (j = 0; j < num_of_features; j++) {
			inData[i].features[j] = (inData[i].features[j] - min[j])
					/ (max[j] - min[j]);
		}
	}
	double end = omp_get_wtime();
	normalizationTime = end - begin;
	normalizedData = inData;
}

void Normalization::findMinMax() {
	int i, j;
	int num_of_features = NUM_OF_FEATURES;
	double begin = omp_get_wtime();

	for( i=0;i<num_of_features;i++){
		min[i]= numeric_limits<int>::max();
	}

	#pragma omp parallel for default(none) shared(inData,min,max,num_of_features,inDataSize) private(i,j)
	for ( i = 0; i < inDataSize; i++) {
		for ( j = 0; j < num_of_features; j++) {
			if (min[j] > inData[i].features[j]) {
				min[j] = inData[i].features[j];
			}

			if (max[j] < inData[i].features[j]) {
				max[j] = inData[i].features[j];
			}
		}
	}

	double end = omp_get_wtime();
	minMaxTime = end - begin;
}

double Normalization::getNormalizationTime() {
	return normalizationTime;
}

double Normalization::getMinMaxTime(){
	return minMaxTime;
}

