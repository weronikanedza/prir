#pragma once

#include <string>
#include <vector>
#define NUM_OF_FEATURES 4

using namespace std;

class Row {
public:
	vector<double> features;
	int category;
	double distance;
	int prediction;
	Row(vector<double> m_features, int m_category) :
			features(m_features), category(m_category) {
	}
	;
};

struct CompareRows {
	bool operator ()(const Row &row1, const Row &row2) {
		//kolejność - rosnąco
		if (row1.distance > row2.distance)
			return true;

		if (row1.distance < row2.distance)
			return false;

		return false;
	}
};