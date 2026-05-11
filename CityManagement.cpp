#include <iostream>
#include <vector>

using namespace std;

// days: length of array. Off by 1!

// fac[] marks down entries of factory, with index being the date the factory was built, and content being the capacity of that factory
// wrk[] marks down entries of workers, with index being the date. True means a new worker.
// idleWkr is self-explanatory.
// To calculate final gain: a matrix of occupied[date][factories]. For example at day 2,
// a factory which was set up on day 0 is occupied, which would be:
// [[...day0...], [...day1...], [1, 0, 0, ...]]

int gain(const int capacity, const int period) {
    return capacity * period;
}

int getPeriod(const int current, const int days) {
    return days - current;
}

int findMaxGain(const int* fac, int current, const int days) {
    int workday = getPeriod(current, days); // days is already +1
    if (workday <= 0) return 0;
    int curGain = 0, maxGain = 0;
    while (current < days) {
        curGain = gain(fac[++current], --workday);
        if (curGain > maxGain)  maxGain = curGain;
    }
    return maxGain;
}

void factory(const int* fac, const int current, const int days, int* idleWkr, vector<bool>& occupiedThatDay) {
     if (*idleWkr > 0) {
         if (gain(fac[current], days - current) > findMaxGain(fac, current, days)) {
             --*idleWkr;
             occupiedThatDay[current] = true;
         }
     } else {
         occupiedThatDay[current] = true;
     }
}

int getProfit(const int* fac, const int days, const vector<vector<bool>>& occupied) {
    int profit = 0;
    for (int i = 0; i < days; i++) {
        for (int j = 0; j < days; j++) {
            if (occupied.at(i).at(j)) {
                profit += fac[i];
            }
        }
    }
    return profit;
}