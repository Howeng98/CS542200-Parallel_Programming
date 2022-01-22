#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long long pixels = 0;
unsigned long long result = 0;

struct arg
{
	unsigned long long r;
	unsigned long long k;	
	unsigned long long start;
	unsigned long long end;

};

void* calculate_pixels(void* arg) {
    struct arg* arg_temp = (struct arg*)arg;
	unsigned long long idx, temp_sum=0;
	for(idx=arg_temp->start; idx<=arg_temp->end;idx++){
		temp_sum += ceil(sqrtl(arg_temp->r*arg_temp->r - idx*idx));
	}
	pthread_mutex_lock(&mutex);
	pixels += temp_sum;

	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exactly 2 arguments!\n");
		return 1;
	}
	
	unsigned long long r = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);		
	unsigned long long i;

	int num_thread = 4;
	unsigned long long num_per_t = r/4;
	pthread_t threads[num_thread];
	struct arg args;

	for(i=0;i<num_thread;i++){
		if(i != num_thread-1){
			args.r = r;
			args.k = k;
			args.start = i*num_per_t;
			args.end = (i+1)*num_per_t-1;
		}
		else{			
			args.r = r;
			args.k = k;
			args.start = i*num_per_t;			
			args.end = r-1;			
		}
		pthread_create(&threads[i], NULL, calculate_pixels, (void*)&args);
		pthread_join(threads[i], NULL);
	}

	for(i=0;i<num_thread;i++){		
		result += pixels;
	}
	
	printf("%llu\n", (4 * pixels) % k);
	pthread_exit(NULL);
}
