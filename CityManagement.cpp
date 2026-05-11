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

int findMaxUnoccupiedGain(const int* fac, int current, const int days, const vector<bool>& occupiedThatDay) {
    int workday = getPeriod(current, days); // days is already +1
    if (workday <= 0) return 0;
    int curGain = 0, maxGain = 0;
    while (current < days) {
        curGain = gain(fac[++current], --workday);
        if (curGain > maxGain && !occupiedThatDay.at(current))  maxGain = curGain;
    }
    return maxGain;
}

void setIdleWkr(int numOfWkr, const int days, vector<bool>& occupiedThatDay, int* idleWkr) {
    int working = 0;
    for (int i = 0; i < days; i++) {
        if (occupiedThatDay.at(i)) ++working;
    }
    *idleWkr = numOfWkr - working;
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

int nextNewWorker(const bool* wkr, int current, const int days) {
    while (current < days) {
        if (wkr[++current]) {
            return current;
        }
    }
    return days - 1;
}

int numberOfWorkers(const bool* wkr, const int days) {
    int result = 0;
    for (int i = 0; i < days; i++) {
        if (wkr[i]) ++result;
    }
    return result;
}

void worker(const int* fac, const bool* wkr, const int current, const int days, int* idleWkr, vector<vector<bool>>& occupied) {
    const int newWkr = nextNewWorker(wkr, current, days);
    const int period = newWkr - current + 1;
    const int numOfWkr = numberOfWorkers(wkr, current);
    for (int j = 0; j < numOfWkr; j++) {
        for (int i = 0; i < current; i++) {
            if (gain(fac[i], period) > findMaxUnoccupiedGain(fac, i, newWkr, occupied.at(current))) {
                occupied.at(current).at(i) = true;
                break;
            }
        }
    }
    setIdleWkr(numOfWkr, days, occupied.at(current), idleWkr);
}

int main() {
    int rounds = 0;
    cin >> rounds;
    for (int i = 0; i < rounds; i++) {
        int days = 0;
        cin >> days;
        int fac[days];
        bool wkr[days];
        int idleWkr;
        vector<vector<bool>> occupied(days, vector<bool>(days, false));
        for (int j = 0; j < days; j++) {
            char c; cin >> c;
            if (c == 'F') {
                int capacity; cin >> capacity;
                fac[j] = capacity;
                wkr[j] = false;
            } else if (c == 'W') {
                wkr[j] = true;
                fac[j] = 0;
            } else return -1;
        }

        for (int j = 0; j < days; j++) {
            if (wkr[j]) {
                worker(fac, wkr, j, days, &idleWkr, occupied);
            } else {
                occupied.at(j) = occupied.at(j-1);
                factory(fac, j, days, &idleWkr, occupied.at(j));
            }
        }
        cout << getProfit(fac, days, occupied) << endl;
    }
}