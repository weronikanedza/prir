#include "Normalization.hpp"

void Normalization::normalize() {
	findMinMax();

	double begin = omp_get_wtime();
	for (int i = 0; i < inData.size(); i++) {
		for (int j = 0; j < 4; j++) {
			inData[i].features[j] = (inData[i].features[j] - min[j])
					/ (max[j] - min[j]);
		}
	}
	double end = omp_get_wtime();
	normalizationTime = end - begin;
	normalizedData = inData;
}

void Normalization::findMinMax() {
	double begin = omp_get_wtime();

	for (int i = 0; i < inData.size(); i++) {
		for (int j = 0; j < 4; j++) {
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

