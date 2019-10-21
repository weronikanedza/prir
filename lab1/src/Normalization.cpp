#include "Normalization.hpp"
#include<limits>
#include<iostream>
#include "KNNRow.hpp"

using namespace std;

void Normalization::normalize(int argc, char *argv[]) {
	findMinMax(argc, argv);

	int num_of_features = NUM_OF_FEATURES;
	int i, j;
	int numprocs, myid, islave;

	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	int iterationsPerProcess = inDataSize / numprocs;

	//keep data about all catrgories in one process and features
	int buf_category[iterationsPerProcess];
	double buf_features[iterationsPerProcess * NUM_OF_FEATURES];
	KNNRow rows[iterationsPerProcess];

	int inDataIdx = myid * iterationsPerProcess;

	//fill data for each process
	for (i = 0; i < iterationsPerProcess; i++) {
		buf_category[i] = inData[inDataIdx].category;

		for (j = 0; j < num_of_features; j++) {
			buf_features[i * num_of_features + j] =
					(inData[inDataIdx].features[j] - min[j])
							/ (max[j] - min[j]);
		}

		++inDataIdx;
	}

	//gather in one all data
	int *all_categories = nullptr;
	double *all_features = nullptr;

	if (myid == 0) {
		all_categories = new int[iterationsPerProcess * numprocs];
		all_features = new double[iterationsPerProcess * numprocs
				* sizeof(KNNRow)];
	}

	MPI_Gather(buf_category, iterationsPerProcess, MPI_INT, all_categories,
			iterationsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(buf_features, iterationsPerProcess * NUM_OF_FEATURES, MPI_DOUBLE,
			all_features, iterationsPerProcess * NUM_OF_FEATURES, MPI_DOUBLE, 0,
			MPI_COMM_WORLD);

	//clean them in one beautiful structure
	if (myid == 0) {
		KNNRow allNormalizedData[iterationsPerProcess * numprocs];
		memset(allNormalizedData, 0,
				iterationsPerProcess * numprocs * sizeof(KNNRow));

		for (int i = 0; i < numprocs; i++) {
			for (int j = 0; j < iterationsPerProcess; j++) {
				int data_id = i * iterationsPerProcess + j;
				normalizedData[data_id].category = all_categories[data_id];

				for (int k = 0; k < all_categories[data_id]; ++k) {
					normalizedData[data_id].features[k] = all_features[i
							* iterationsPerProcess * NUM_OF_FEATURES
							+ j * NUM_OF_FEATURES];
				}
			}
		}
	}


	delete[] all_categories;
	delete[] all_features;
}

void Normalization::findMinMax(int argc, char *argv[]) {
	int i, j;
	int num_of_features = NUM_OF_FEATURES;
	int numprocs, myid, islave;

	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	for (i = 0; i < num_of_features; i++) {
		min[i] = numeric_limits<int>::max();
	}

	double begin = MPI_Wtime();

	if (myid == 0) {
		for (islave = 1; islave < numprocs; islave++) {
			MPI_Send(&inDataSize, 1, MPI_INTEGER, islave, MTAG1,
					MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&inDataSize, 1, MPI_INTEGER, 0, MTAG1, MPI_COMM_WORLD,
				&status);
	}

	for (i = myid; i < inDataSize; i += numprocs) {

		for (j = 0; j < num_of_features; j++) {
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

double Normalization::getMinMaxTime() {
	return minMaxTime;
}

vector<Row> Normalization::getNormalizedData() {
	return normalizedData;

}
