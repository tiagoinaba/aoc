#include "../day4/thelib.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

vector<int> getNextStep(vector<int>::iterator begin, vector<int>::iterator end) {
    vector<int> next;

    for (; begin != end - 1; begin++) {
        next.push_back(*(begin + 1) - *begin);
    }

    return next;
}

vector<vector<int>> getSteps(vector<int> start) {
    vector<vector<int>> history;
    vector<int> next = start;
    
    while (true) {
        history.push_back(next);
        next = getNextStep(next.begin(), next.end());

        if (all_of(next.begin(), next.end(), [](int el) { return el == 0; })) {
            return history;
        }
    }
}

int getNext(vector<vector<int>>::reverse_iterator begin, vector<vector<int>>::reverse_iterator end) {
    int next;

    for (; begin != end - 1; begin++) {
        next = *((begin + 1)->begin()) - *(begin->end() - 1);
        (begin + 1)->push_back(next);
    }

    return next;
}

int main(int argc, char* argv[]) {
    string file = "input";

    ifstream content(file);
    string line;

    int sum = 0;

    while (getline(content, line)) {
        vector<string> histStr = explode(line, " ");

        vector<int> history;

        for (auto str : histStr) {
            history.push_back(stoi(str));
        }

        vector<vector<int>> expanded = getSteps(history);
        sum += getNext(expanded.rbegin(), expanded.rend());
    }

    cout << sum << '\n';
}
