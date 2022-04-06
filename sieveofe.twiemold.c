#include <stdio.h>
#include <math.h>
#define arrayMax 200
#define stopValue floor(sqrt(arrayMax)) + 1
// TODO: 0 indexing problem?

int main() {
    char done = 0;
    char nums[arrayMax];
    for (int i = 2; i < arrayMax; ++i) {
        nums[i] = 1;
    }
//    while not done {
    while (!(done)) {
        char pPicked = 0;
        // let p be the smallest integer less than or equal to stopValue
        // and not yet crossed off and not marked as visited
        int p = 2;
        for (int i = 2; i <= stopValue; ++i) {
            if (nums[i] != 0 && nums[i] != -1) {
                p = i;
                pPicked = 1;
            }
        }
        // if there is no such number {
        // done = 1
        // } else {
        // mark p as visited
        // cross off all multiples of p, starting at 2*p and ending at arrayMax
        if (!(pPicked)) {
            pPicked = 1;
            done = 1;
        } else {
            nums[p] = -1;
            // cross off all multiples of p, starting at 2*p and ending at arrayMax
            int val = 2;
            int multiple = val * p;
            while (multiple < arrayMax) {
                nums[multiple] = 0;
                val++;
                multiple = val * p;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < arrayMax; ++i) {
        if (nums[i] == 1 || nums[i] == -1) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}
