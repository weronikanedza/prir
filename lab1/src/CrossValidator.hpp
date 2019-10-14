#include "Row.hpp"
#include <vector>

class CrossValidator {
private:
	vector<Row> trainingSet;
	vector<Row> testingSet;
public:
	CrossValidator(vector<Row> trainingSet, vector<Row> testingSet) :
			trainingSet(trainingSet), testingSet(testingSet) {
	}
	;
	void valdate();
};
