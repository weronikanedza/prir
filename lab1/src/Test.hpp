#include <string>

using namespace std;

class Test{
public:
	double features[6];
	string category;
	string prediction;
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
