#pragma once
#include "Row.hpp"

class Standarization {
private:
	vector<Row> standarizedData;
	vector<Row> inData;
	double average[NUM_OF_FEATURES];
	double deviation[NUM_OF_FEATURES];
	double minMaxTime;
	double deviationTime;
public:
	Standarization(vector<Row> inData):inData(inData){};
	void standarize();
	void calcAverage();
	void calcDeviation();
	double getMinMaxTime;
	double getDeviationTime;
};
