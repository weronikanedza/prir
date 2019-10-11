#pragma once
#include "Row.hpp"
#include "omp.h"

class Normalization {
private:
	vector<Row> normalizedData;
	vector<Row> inData;
	double normalizationTime;
	double minMaxTime;
	double min[NUM_OF_FEATURES] = {100,100,100,100};
	double max[NUM_OF_FEATURES];
public:
	Normalization(vector<Row> inData) :
			inData(inData) {};
	double getNormalizationTime();
	void normalize();
	void findMinMax();
};
