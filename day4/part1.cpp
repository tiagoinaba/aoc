#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "thelib.h"

using namespace std;

bool findInSortedVec(vector<string> vec, string toFind) {
    long half = vec.size() / 2;

    if (half == 0 && vec[half] != toFind) return false;

    if (vec[half] == toFind) return true;
    else if (vec[half] > toFind) {
        vector<string> firstHalf(vec.begin(), vec.begin() + half);
        return findInSortedVec(firstHalf, toFind);
    } else {
        vector<string> secondHalf(vec.begin() + half, vec.end());
        return findInSortedVec(secondHalf, toFind);
    } 
}

int main(int argc, char* argv[]) {
    ifstream contents("./input");
    string line;

    int pileSum = 0;

    while (getline(contents, line)) {
        vector<string> left = explode(explode( explode(line, ": ")[1], " | " )[0], " ");
        vector<string> right = explode(explode( explode(line, ": ")[1], " | " )[1], " ");

        int cardValue = 0;

        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        for (int i = 0; i < left.size(); i++) {
            bool found = findInSortedVec(right, left[i]);
            if (found) cardValue++;
        }

        if (cardValue > 0) pileSum += pow(2, cardValue -1);
    }

    cout << "result: " << pileSum << endl;
}
