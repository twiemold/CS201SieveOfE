#include <stdio.h>
#include <math.h>
#define M 200
#define S floor(sqrt(M)) + 1
// TODO: 0 indexing problem?

int main() {
    char done = 0;
    char nums[M];
    for (int i = 2; i < M; ++i) {
        nums[i] = 1;
    }
//    while not done {
    while (!(done)) {
        char pPicked = 0;
        // let p be the smallest integer less than or equal to S
        // and not yet crossed off and not marked as visited
        int p = 2;
        for (int i = 2; i <= S; ++i) {
            if (nums[i] != 0 && nums[i] != -1) {
                p = i;
                pPicked = 1;
            }
        }
        // if there is no such number {
        // done = 1
        // } else {
        // mark p as visited
        // cross off all multiples of p, starting at 2*p and ending at M
        if (!(pPicked)) {
            pPicked = 1;
            done = 1;
        } else {
            nums[p] = -1;
            // cross off all multiples of p, starting at 2*p and ending at M
            int val = 2;
            int multiple = val * p;
            while (multiple < M) {
                nums[multiple] = 0;
                val++;
                multiple = val * p;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < M; ++i) {
        if (nums[i] == 1 || nums[i] == -1) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}
