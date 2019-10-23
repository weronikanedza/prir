#include "Normalization.hpp"
#include<limits>
#include<iostream>
#include "KNNRow.hpp"

using namespace std;

void Normalization::normalize(int argc, char *argv[]) {
	findMinMax(argc, argv);

	int num_of_features = NUM_OF_FEATURES;
	int numprocs, myid, islave;

	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	int num_of_features = NUM_OF_FEATURES;
	int i, j;

	double begin = MPI_Wtime();

	int iterationsPerProcess;

	//send information about data size
	if (myid == 0) {
		iterationsPerProcess = inDataSize / numprocs;
		for (islave = 1; islave < numprocs; islave++) {
			MPI_Send(&iterationsPerProcess, 1, MPI_INTEGER, islave, 4,
					MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&iterationsPerProcess, 1, MPI_INTEGER, 0, 4, MPI_COMM_WORLD,
				&status);
	}

	MPI_Barrier (MPI_COMM_WORLD);

	for (i = 0; i < inDataSize; i++) {
		for (j = 0; j < num_of_features; j++) {
			inData[i].features[j] = (inData[i].features[j] - min[j])
					/ (max[j] - min[j]);
		}
	}

	double end = MPI_Wtime();
	normalizationTime = end - begin;
	normalizedData = inData;
}

//void Normalization::normalize(int argc, char *argv[]) {
//	findMinMax(argc, argv);
//
//	int num_of_features = NUM_OF_FEATURES;
//	int numprocs, myid, islave;
//	double local_category[inDataSize];
//
//	MPI_Status status;
//	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
//	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
//
//	int iterationsPerProcess;
//
//	//send information about data size
//	if (myid == 0) {
//		iterationsPerProcess = inDataSize / numprocs;
//		for (islave = 1; islave < numprocs; islave++) {
//			MPI_Send(&iterationsPerProcess, 1, MPI_INTEGER, islave, 4,
//					MPI_COMM_WORLD);
//		}
//	} else {
//		MPI_Recv(&iterationsPerProcess, 1, MPI_INTEGER, 0, 4, MPI_COMM_WORLD,
//				&status);
//	}
//
//	//keep data about all catrgories in one process and features
//	int buf_category[iterationsPerProcess];
//	double buf_features[iterationsPerProcess * NUM_OF_FEATURES];
//	KNNRow rows[iterationsPerProcess];
//
//	int inDataIdx = myid * iterationsPerProcess;
//
//	//fill data for each process
//	for (int i = 0; i < iterationsPerProcess; i++) {
//		buf_category[i] = inData[inDataIdx].category;
//
//		for (int j = 0; j < num_of_features; j++) {
//			buf_features[i * num_of_features + j] =
//					(inData[inDataIdx].features[j] - min[j])
//							/ (max[j] - min[j]);
////
////			cout << myid << " BUF " << buf_features[i * num_of_features + j]
////						<< " in data " << inData[inDataIdx].features[j]
////						<< " min j " << min[j] << " max[j] " <<max[j] <<endl;
//		}
//
//		++inDataIdx;
//	}
//
////	if (myid == 0) {
////		cout<< " DUPA  "<<endl;
////		for (int i = 0; i < inDataSize * NUM_OF_FEATURES; i++) {
////			cout << buf_features[i] << " ";
////		}
////	}
//
//	//fill data for each process
//
////	if (myid == 0) {
////		cout << "ZERO : " << endl;
////		for (int i = 0; i < iterationsPerProcess; i++) {
////			cout << " Category " << buf_category[i] << "  ------   ";
////
////			for (int j = 0; j < num_of_features; j++) {
////
////				cout << buf_features[i * num_of_features + j] << " ";
////			}
////			cout << endl;
////			++inDataIdx;
////		}
////	}
////
////
////	if (myid == 1) {
////		cout << "PIERWSZY : " << endl;
////		for (int i = 0; i < iterationsPerProcess; i++) {
////			cout << " Category " << buf_category[i] << "  ------   ";
////
////			for (int j = 0; j < num_of_features; j++) {
////
////				cout << buf_features[i * num_of_features + j] << " ";
////			}
////			cout << endl;
////			++inDataIdx;
////		}
////	}
//
//	MPI_Barrier (MPI_COMM_WORLD);
//
//	int all_categories[iterationsPerProcess * numprocs];
//	double all_features[iterationsPerProcess * numprocs * NUM_OF_FEATURES];
//
//	MPI_Gather(buf_category, iterationsPerProcess, MPI_INT, all_categories,
//			iterationsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
//	MPI_Gather(buf_features, iterationsPerProcess * NUM_OF_FEATURES, MPI_DOUBLE,
//			all_features, iterationsPerProcess * NUM_OF_FEATURES, MPI_DOUBLE, 0,
//			MPI_COMM_WORLD);
//
//	MPI_Barrier(MPI_COMM_WORLD);
//
//
//
//	if (myid == 0) {
//
//		for (islave = 1; islave < numprocs; islave++) {
//			MPI_Send(all_categories, inDataSize, MPI_INTEGER, islave, 5,
//					MPI_COMM_WORLD);
//			MPI_Send(all_features, inDataSize * NUM_OF_FEATURES, MPI_DOUBLE,
//					islave, 6, MPI_COMM_WORLD);
//		}
//
//	} else {
//		MPI_Recv(all_categories, inDataSize, MPI_INTEGER, 0, 5, MPI_COMM_WORLD,
//				&status);
//		MPI_Recv(all_features, inDataSize * NUM_OF_FEATURES, MPI_DOUBLE, 0, 6,
//				MPI_COMM_WORLD, &status);
//	}
//
//
//
//	//pack to normal structure
//	int idx = 0;
//	for (int i = 0; i < inDataSize; i++) {
//		Row row;
//		row.category = all_categories[i];
//		for (int j = 0; j < NUM_OF_FEATURES; j++) {
//			row.features.push_back(all_features[idx++]);
//		}
//		normalizedData.push_back(row);
//	}
////
////	if (myid == 0) {
////		cout << "NORMALIZED FOR myID " << endl;
////		for (int i = 0; i < inDataSize; i++) {
////			cout << "\n category " << normalizedData[i].category << "   "
////					<< endl;
////			for (int j = 0; j < NUM_OF_FEATURES; j++) {
////				cout << normalizedData[i].features[j] << " ";
////			}
////		}
////
////	}
//
////	delete[] all_categories;
////	delete[] all_features;
//
//}

void Normalization::findMinMax(int argc, char *argv[]) {
	int i, j;
	int num_of_features = NUM_OF_FEATURES;
	MPI_Status status;
	double global_min[NUM_OF_FEATURES];
	double global_max[NUM_OF_FEATURES];

	double local_min[NUM_OF_FEATURES];
	double local_max[NUM_OF_FEATURES];

	for (i = 0; i < num_of_features; i++) {
		local_min[i] = numeric_limits<int>::max();
		local_max[i] = numeric_limits<int>::min();
	}

	int myid, numprocs, islave;
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	double begin = MPI_Wtime();

	for (i = myid; i < inDataSize; i += numprocs) {
		for (j = 0; j < num_of_features; j++) {

			if (local_min[j] > inData[i].features[j]) {
				local_min[j] = inData[i].features[j];
			}

			if (local_max[j] < inData[i].features[j]) {
				local_max[j] = inData[i].features[j];
			}
		}
	}

	MPI_Barrier (MPI_COMM_WORLD);

	for (int i = 0; i < NUM_OF_FEATURES; i++) {
		MPI_Reduce(&local_min[i], &min[i], 1, MPI_DOUBLE, MPI_MIN, 0,
				MPI_COMM_WORLD);
		MPI_Reduce(&local_max[i], &max[i], 1, MPI_DOUBLE, MPI_MAX, 0,
				MPI_COMM_WORLD);
	}

//pass min /max to all
	if (myid == 0) {
		for (islave = 1; islave < numprocs; islave++) {
			MPI_Send(min, NUM_OF_FEATURES, MPI_DOUBLE, islave, 10,
					MPI_COMM_WORLD);
			MPI_Send(max, NUM_OF_FEATURES, MPI_DOUBLE, islave, 11,
					MPI_COMM_WORLD);

		}
	} else {
		MPI_Recv(min, NUM_OF_FEATURES, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD,
				&status);

		MPI_Recv(max, NUM_OF_FEATURES, MPI_DOUBLE, 0, 11, MPI_COMM_WORLD,
				&status);
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
