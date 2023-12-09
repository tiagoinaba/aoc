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
    vector<string> time;
    vector<string> distance;
    vector<long> timesNum;
    vector<long> distancesNum;

    getline(content, line);
    time = explode(explode(line, ":")[1], " ");

    getline(content, line);
    distance = explode(explode(line, ":")[1], " ");

    for (auto w : time) {
        timesNum.push_back(stol(w));
    }

    for (auto w : distance) {
        distancesNum.push_back(stol(w));
    }
    
    long result = 1;

    for (int i = 0; i < distancesNum.size(); i++) {
        result *= waysToBeat(timesNum[i], distancesNum[i]);
    }

    cout << result << '\n';

    return 0;
}
