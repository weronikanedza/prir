#include "Row.hpp"
#include <queue>

class KNN {
private:
	vector<Row> trainingSet;
	vector<Row> testingSet;
	vector<Row> inData;

public:
	KNN(vector<Row> inData) :
			inData(inData) {
	}
	;
	void createSets();
	void knn();
	double calculateEuclideanDist(Row currentRow, Row neighbour);
	int calculatePrediction(
			priority_queue<Row, vector<Row>, CompareRows> neighbours,
			Row testingVal, int K);
	int votePrediction(priority_queue<Row, vector<Row>, CompareRows> neighbours,
			int K);
	double getAccuracy();
};
