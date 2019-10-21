#include "FileLoader.hpp"
#include "KNN.hpp"
#include <math.h>
#include <iostream>
#include "Normalization.hpp"


using namespace std;

int main(int argc , char * argv []) {
	vector<Row> rows = FileLoader().readFile();
	KNN knn = KNN();
	Normalization normalize = Normalization(rows);

	MPI_Status status;
	MPI_Init(&argc,&argv);

	//knn.knn(rows, argc, argv);
	normalize.normalize(argc, argv);

//	knn.knn(rows,argc, argv);

	MPI_Finalize();

	cout << "Normalization time "<<endl;
	cout << normalize.getMinMaxTime() + normalize.getNormalizationTime()<<endl;

//	cout<<"********KNN**************"<<endl;
//	cout << "ACC : " << knn.accuracy<< endl;
//	cout << "TIME : " << knn.knnTime << endl<<endl;

	return 0;
}

