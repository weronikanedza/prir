#pragma once

#include <string>
#include <vector>
#define NUM_OF_FEATURES 6

using namespace std;

class Row {
public:
	vector<double> features;
	string category;
	double distance;
	string prediction;
	Row(vector<double> m_features, string m_category) :
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
