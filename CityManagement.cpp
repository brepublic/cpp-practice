#include <iostream>

using namespace std;

// days: length of array. Off by 1!

int gain(int capacity, int period) {
    return capacity * period;
}

int findMaxGain(int* fac, int current, int days) {
    int workday = days - current; // days is already +1
    if (workday <= 0) return 0;
    int curGain = 0, maxGain = 0;
    while (current < days) {
        curGain = gain(fac[++current], --workday);
        if (curGain > maxGain)  maxGain = curGain;
    }
    return maxGain;
}