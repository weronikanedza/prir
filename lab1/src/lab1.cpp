#include "FileLoader.hpp"
#include "Normalization.hpp"
#include "Standarization.hpp"
#include <math.h>
#include <omp.h>
using namespace std;

int main() {
	vector<Row> rows = FileLoader().readFile();
	Normalization normalization = Normalization(rows);
	Standarization standarization = Standarization(rows);

	normalization.normalize();
	standarization.standarize();

	return 0;
}


