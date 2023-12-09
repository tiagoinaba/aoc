#include "../day4/thelib.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long waysToBeat(long time, long distToBeat) {
    // the function is fn(th, tt) = th(tt - th)
    long min = 0;
    long max = time;

    bool foundMin = false;
    bool foundMax = false;

    while (!foundMin && !foundMax) {
        long minDist = min * (time - min);
        long maxDist = max * (time - max);

        if (minDist > distToBeat && !foundMin) {
            foundMin = true;
        } else min++;

        if (maxDist > distToBeat && !foundMax) {
            foundMax = true;
        } else max--;
    }

    return max - min + 1;
}

int main(int argc, char* argv[]) {
    string fileIn = "./input";

    if (argc > 1) {
        fileIn = argv[1];
    }

    ifstream content(fileIn);

    string line;
    string time;
    string distance;
    vector<int> timesInt;
    vector<int> distancesInt;

    getline(content, line);
    time = explode(line, ":")[1];

    getline(content, line);
    distance = explode(line, ":")[1];

    time.erase(remove(time.begin(), time.end(), ' '), time.end());
    distance.erase(remove(distance.begin(), distance.end(), ' '), distance.end());

    int result = 1;

    result *= waysToBeat(stol(time), stol(distance));

    cout << result << '\n';

    return 0;
}
