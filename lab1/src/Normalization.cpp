#include "Normalization.hpp"
#include<limits>
#include<iostream>
using namespace std;

void Normalization::normalize(int argc, char *argv[] ,int numprocs ,int myid) {
	findMinMax(argc, argv);

	int num_of_features = NUM_OF_FEATURES;
	int i, j;
	int  islave;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Status status;

	double begin = MPI_Wtime();

	if (myid == 0) {
			for (islave = 1; islave < numprocs; islave++) {
				MPI_Send(&inDataSize, 1, MPI_INTEGER, islave, MTAG1, MPI_COMM_WORLD);
			}
		} else {
			MPI_Recv(&inDataSize, 1, MPI_INTEGER, 0, MTAG1, MPI_COMM_WORLD, &status);
		}


	for (i = myid; i < inDataSize; i+=numprocs) {
		for (j = 0; j < num_of_features; j++) {
			inData[i].features[j] = (inData[i].features[j] - min[j])
					/ (max[j] - min[j]);
		}
	}
	double end = MPI_Wtime();
	normalizationTime = end - begin;
	normalizedData = inData;
}

void Normalization::findMinMax(int argc, char *argv[]) {
	int i, j;
	int num_of_features = NUM_OF_FEATURES;
	MPI_Status status;

	for( i=0;i<num_of_features;i++){
		min[i]= numeric_limits<int>::max();
	}

	int myid, numprocs, islave;

	double begin = MPI_Wtime();

	if (myid == 0) {
			for (islave = 1; islave < numprocs; islave++) {
				MPI_Send(&inDataSize, 1, MPI_INTEGER, islave, MTAG1, MPI_COMM_WORLD);
			}
		} else {
			MPI_Recv(&inDataSize, 1, MPI_INTEGER, 0, MTAG1, MPI_COMM_WORLD, &status);
		}


	for ( i = myid; i < inDataSize; i+=numprocs) {
		for ( j = 0; j < num_of_features; j++) {
			if (min[j] > inData[i].features[j]) {
				min[j] = inData[i].features[j];
			}

			if (max[j] < inData[i].features[j]) {
				max[j] = inData[i].features[j];
			}
		}

	}

	double end = MPI_Wtime();
	minMaxTime = end - begin;
}

double Normalization::getNormalizationTime() {
	return normalizationTime;
}

double Normalization::getMinMaxTime(){
	return minMaxTime;
}

vector<Row> Normalization::getNormalizedData(){
	return normalizedData;

}
