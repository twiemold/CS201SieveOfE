#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#define START_VALUE 2
#define UPPER_BOUND 10000000
#define STOP_VALUE floor(sqrt(UPPER_BOUND)) + 1
#define NUM_THREADS 10

void *crossing(char nums[]) {
    char done = 0;
    int chosenStart = START_VALUE;
    while (!(done)) {
        while (!(nums[chosenStart] != -1 && nums[chosenStart] != 0) && chosenStart < STOP_VALUE) {
            chosenStart++;
        }
        if (chosenStart < STOP_VALUE) {
            nums[chosenStart] = -1;
        } else {
            done = 1;
        }
        if (!(done)) {
            int val = 2;
            int multiple = val * chosenStart;
            while (multiple < UPPER_BOUND) {
                nums[multiple] = 0;
                val++;
                multiple = val * chosenStart;
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[NUM_THREADS];
    char* nums = (char*) malloc((UPPER_BOUND * sizeof(char)));
    int i;
    for (i = START_VALUE; i < UPPER_BOUND; ++i) {
        nums[i] = 1;
    }

    // create and start the threads
    for (i = 0; i<NUM_THREADS; ++i) {
        // create and start a child thread
        pthread_create(&tid[i], NULL, crossing, nums);
    }
    // wait for the child threads to terminate
    for (i=0; i<NUM_THREADS; ++i) {
        pthread_join(tid[i], NULL);
    }

    int count = 0;
    for (i = 0; i < UPPER_BOUND; ++i) {
        if (nums[i] == 1 || nums[i] == -1) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}
