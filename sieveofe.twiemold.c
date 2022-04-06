#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define START_VALUE 2
#define UPPER_BOUND 1000000000
#define STOP_VALUE floor(sqrt(UPPER_BOUND)) + 1
#define NUM_THREADS 4

typedef struct {
    char* numPtr;
    pthread_mutex_t* mutexPtr;
} SieveData;


void *sieve(void *param) {
    SieveData *data;
    data = (SieveData *) param;

    char done = 0;
    int chosenStart = START_VALUE;
    while (!(done)) {
        pthread_mutex_lock(data->mutexPtr);
        while (!(data->numPtr[chosenStart] != -1 && data->numPtr[chosenStart] != 0) && chosenStart < STOP_VALUE) {
            chosenStart++;
        }
        if (chosenStart < STOP_VALUE) {
            data->numPtr[chosenStart] = -1;
        } else {
            done = 1;
        }
        pthread_mutex_unlock(data->mutexPtr);
        if (!(done)) {
            int val = 2;
            int multiple = val * chosenStart;
            while (multiple < UPPER_BOUND) {
                data->numPtr[multiple] = 0;
                val++;
                multiple = val * chosenStart;
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    SieveData data;
    pthread_t tid[NUM_THREADS];
    char* nums = (char*) malloc((UPPER_BOUND * sizeof(char)));
    int i;
    for (i = START_VALUE; i < UPPER_BOUND; ++i) {
        nums[i] = 1;
    }

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_t* mutexPtr;
    mutexPtr = &mutex;

    data.numPtr = nums;
    data.mutexPtr = mutexPtr;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    // create and start the threads
    for (i = 0; i<NUM_THREADS; ++i) {
        // create and start a child thread
        pthread_create(&tid[i], NULL, sieve, &data);
    }
    // wait for the child threads to terminate
    for (i=0; i<NUM_THREADS; ++i) {
        pthread_join(tid[i], NULL);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used = %f\n", cpu_time_used);

    int count = 0;
    for (i = 0; i < UPPER_BOUND; ++i) {
        if (nums[i] == 1 || nums[i] == -1) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}
