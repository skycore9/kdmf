#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstring>

#include "io.h"
#include "fjlt.h"
#include "parSort.h"
#include "rerank.h"
#include "build_tree.h"
#include "myRNG.h"

using namespace std;

extern int S;
extern int D;
extern double** Pv;
extern int** Iall;

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Usage: ./a.out n D\n");
		exit(-1);
	}
	int n = (int) pow(2,atoi(argv[1]));
	D = (int) pow(2,atoi(argv[2]));

    int K = D/8;
	//printf("Size = %d, dimension = %d threads = %d\n", atoi(argv[1]), atoi(argv[2]), omp_get_max_threads());

	float *init_data = (float*) malloc(n*D*sizeof(float));
	memset(init_data, 0, n*D*sizeof(float));

    for(int i=0; i<D; i++){
        for(int j=0; j<n; j++){
            init_data[i+D*j] = rand_float(-1,1);
        }
    }

    float *result;
    result = FJLT(init_data, n, K, D);

    D = K;
    
	myRNG rng;
	rng.resetSeed(10215);
	double t1, t2, t3, t4;
	double* Data[D];
	//Generate random data
	for(int i = 0; i < D; i++) {
		double* t = (double*) malloc(n*sizeof(double));
		//printf("Generating data for %d dimension\n",i);
		for(int j = 0; j < n; j++) {
			*(t + j) = result[i + j*D];
		}
		Data[i] = t;
	}


    free(init_data);
    free(result);

	t1 = omp_get_wtime();
	//Create index vectors for each dimension and do rank sort
	int* I[D];
	//Sorting ranks in all dimensions
	for(int i = 0; i < D; i++) {
		int* index = (int*) malloc(n *sizeof(int));
		I[i] = index;
		for(int j=0; j < n; j++) {
			*(I[i] + j) = j;
		}
		if(!index)  { printf("Index is null\n"); exit(-1); }
		if(!Data[i]) { printf("Data pointer null\n"); exit(-1); }
		//printf("Entering ranksort for %d dimension\n",i);
		seqShellSort((float*)Data[i],I[i],n);
		//printf("Finished ranksort for %d dimension\n",i);
	}
	t2 = omp_get_wtime();
	//printf("Sort Completed \n");
	Iall = &(I[0]);
	Pv = &(Data[0]);
	S = 1;
	
	//Tree building
	t3 = omp_get_wtime();
	tree_node* head = build_tree(n);
	t4 = omp_get_wtime();
	//printf("Time taken for sorting  = %f\n", t2 - t1);
	//printf("Time taken to build the tree = %f\n", t4 - t3);
	//printf("Total time taken = %f\n\n", t4 - t1);
	printf("%d %d %f\n", atoi(argv[1]), omp_get_max_threads(),t4-t3);
	//releasing dnamically allocated memory
	delete_tree(head);
	for(int i = 0; i < D; i++) {
		free(I[i]);
		free(Data[i]);
	}
	return 0;
}

