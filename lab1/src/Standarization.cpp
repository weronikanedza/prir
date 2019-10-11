#include "Standarization.hpp"
#include "omp.h"
#include "math.h"
void Standarization::standarize() {
	calcAverage();
	calcDeviation();
	double begin = omp_get_wtime();

	for (int i = 0; i < inData.size(); i++) {
		for (int j = 0; j < 4; j++) {
			inData[i].features[j] = (inData[i].features[j] - average[j])
					/ deviation[j];
		}
	}

	double end = omp_get_wtime();
}

void Standarization::calcAverage(){
	double sum[4];

	double begin = omp_get_wtime();

	int featureSize = 4;
	int size = inData.size();
	int i, j;

	#pragma omp parallel for shared(size,sum,featureSize,inData) private(i,j)
	for (i = 0; i < size; i++) {
		for (j = 0; j < featureSize; j++) {
			sum[j] += inData[i].features[j];
		}
	}

	double end = omp_get_wtime();
	deviationTime = end - begin;

	for (int j = 0; j < 4; j++) {
		average[j] = sum[j] / inData.size();
	}
}

void Standarization::calcDeviation(){
	double variation[4];

	double begin = omp_get_wtime();

	for (int i = 0; i < inData.size(); i++) {
		for (int j = 0; j < 4; j++) {
			variation[j] += pow(inData[i].features[j] - average[j], 2)
					/ inData.size();
		}
	}
	double end = omp_get_wtime();
	deviationTime = end - begin;
	for (int j = 0; j < 4; j++) {
		deviation[j] = sqrt(variation[j]);
	}
}
