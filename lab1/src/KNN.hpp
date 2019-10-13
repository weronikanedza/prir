#include "Row.hpp"
#include <queue>

class KNN {
private:
	vector<Row> trainingSet;
	vector<Row> testingSet;
	vector<Row> inData;
	int inDataSize;
	double knnTime;
public:
	KNN(vector<Row> inData) :
			inData(inData), inDataSize(inData.size()) {
	}
	;
	void createSets();
	void knn();
	double calculateEuclideanDist(Row currentRow, Row neighbour);
	string calculatePrediction(
			priority_queue<Row, vector<Row>, CompareRows> neighbours,
			Row testingVal, int K);
	string votePrediction(
			priority_queue<Row, vector<Row>, CompareRows> neighbours, int K);
	double getAccuracy();
	double getKnnTime();
};
