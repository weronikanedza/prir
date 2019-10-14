#include <string>
#include "Row.hpp"

using namespace std;

class Test{
public:
	double features[NUM_OF_FEATURES];
	int category;
	int prediction;
	double distance;
};

struct CompareTest {
	bool operator ()(const Test &row1, Test  &row2) {
		//kolejność - rosnąco
		if (row1.distance > row2.distance)
			return true;

		if (row1.distance < row2.distance)
			return false;

		return false;
	}
};
