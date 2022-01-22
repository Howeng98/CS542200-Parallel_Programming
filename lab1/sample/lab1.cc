#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exactly 2 arguments!\n");
		return 1;
	}
	// global variable and arguments
	int rank , size;
	// double starttime, endtime;
	unsigned long long r = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);	
	
	// init MPI for each rank
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// variable **The variable that involved into each process should be definied after MPI initialized**
	MPI_Status status;
	unsigned long long pixels = 0;
	unsigned long long result = 0;		
	unsigned long long startval = r*rank/size;
	unsigned long long endval   = r*(rank+1)/size;	
	
	for (unsigned long long x = startval; x<endval; x++){
		pixels += ceil(sqrtl(r*r - x*x));		
	}
	
	if(rank!=0){
		MPI_Send(&pixels, 1, MPI_UNSIGNED_LONG_LONG, 0, 1, MPI_COMM_WORLD);
	}
	else{
		for(unsigned long long rank_num=1; rank_num<size; rank_num++){
			MPI_Recv(&result, 1, MPI_UNSIGNED_LONG_LONG, rank_num, 1, MPI_COMM_WORLD, &status);
			pixels %= k;
			pixels += result;
		}
		printf("%llu\n", (4 * pixels) % k);
	}
	
	MPI_Finalize();

	return 0;
}
