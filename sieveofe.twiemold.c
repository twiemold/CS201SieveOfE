#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#define START_VALUE 2
#define UPPER_BOUND 10000000
#define NUM_THREADS 4

typedef struct {
    int startValue;
    int stopValue;
    long upperBound;
    char* numPtr;
    pthread_mutex_t* mutexPtr;
} SieveData;


void *sieve(void *param) {
    SieveData *data;
    data = (SieveData *) param;

    char done = 0;
    int chosenStart = data->startValue;
    while (!(done)) {
        pthread_mutex_lock(data->mutexPtr);
        while (!(data->numPtr[chosenStart] != -1
                && data->numPtr[chosenStart] != 0)
                && chosenStart < data->stopValue) {
            chosenStart++;
        }
        if (chosenStart < data->stopValue) {
            data->numPtr[chosenStart] = -1;
        } else {
            done = 1;
        }
        pthread_mutex_unlock(data->mutexPtr);
        if (!(done)) {
            int val = 2;
            int multiple = val * chosenStart;
            while (multiple < data->upperBound) {
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
    pthread_mutex_t* mutexPtr = &mutex;

    data.numPtr = nums;
    data.mutexPtr = mutexPtr;
    data.startValue = START_VALUE;
    data.upperBound = UPPER_BOUND;
    data.stopValue = floor(sqrt(UPPER_BOUND)) + 1;

    for (i = 0; i<NUM_THREADS; ++i) {
        // create and start a child thread
        pthread_create(&tid[i], NULL, sieve, &data);
    }
    for (i=0; i<NUM_THREADS; ++i) {
        pthread_join(tid[i], NULL);
    }

    int count = 0;
    for (i = 0; i < UPPER_BOUND; ++i) {
        if (nums[i] == 1 || nums[i] == -1) {
            count++;
        }
    }
    printf("Number of primes between %d and %d: %d",START_VALUE, UPPER_BOUND, count);
    free(nums);

    return 0;
}
