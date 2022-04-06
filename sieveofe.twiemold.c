#include <stdio.h>
#include <math.h>
#define startValue 2
#define upperBound 200
#define stopValue floor(sqrt(upperBound)) + 1

int main() {
    char done = 0;
    char nums[upperBound];
    for (int i = startValue; i < upperBound; ++i) {
        nums[i] = 1;
    }

    int chosenStart = startValue;
    while (!(done)) {
        while (!(nums[chosenStart] != -1 && nums[chosenStart] != 0) && chosenStart < stopValue) {
            chosenStart++;
        }
        if (chosenStart < stopValue) {
            nums[chosenStart] = -1;
        } else {
            done = 1;
        }
        if (!(done)) {
            int val = 2;
            int multiple = val * chosenStart;
            while (multiple < upperBound) {
                nums[multiple] = 0;
                val++;
                multiple = val * chosenStart;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < upperBound; ++i) {
        if (nums[i] == 1 || nums[i] == -1) {
            count++;
        }
    }
    printf("%d", count);

    return 0;
}
