#include "Test.hpp"
#include "Row.hpp"

class KNNBeta
{
public:
	Test *test;
	Test *train;
	void knn(vector<Row> rows);
	void splitData(vector<Row> allData);
	string calcPrediction(Test testVal, int K);
	int testSize;
	int trainSize;
	double calcDist(Test current,Test trainValue);
};
