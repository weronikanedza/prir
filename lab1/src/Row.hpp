#pragma once

#include <string>
#include <vector>
#define NUM_OF_FEATURES 4

using namespace std;

class Row {
	public:
		vector<double> features;
		string category;
		Row(vector<double> m_features, string m_category) :
		features(m_features),category(m_category) {};
};
