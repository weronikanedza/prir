#include "Test.hpp"
#include "Row.hpp"

class KNNBeta
{
public:
	Test *test;
	Test *train;
	vector<Test> trainSet;
	vector<Test> testSet;
	void knn(vector<Row> rows);
	void splitData(vector<Row> allData);
	int calcPrediction(Test testVal, int K);
	int testSize;
	int trainSize;
	double calcDist(Test current,Test trainValue);
};
