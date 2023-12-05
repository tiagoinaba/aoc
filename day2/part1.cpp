#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include "day2.h"

using namespace std;

const int RED = 12;
const int GREEN = 13;
const int BLUE = 14;

int main(int argc, char *argv[]) {
    string input = "./input";

    if (argc > 1) {
        input = argv[1];
    }

    ifstream file(input);

    string line;

    int sum = 0;

    while (getline(file, line)) {
        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        cout << "========================" << endl;

        vector<string> vec = explode(line, ':');

        int gameId = stoi(vec[0].substr(5, variant_npos));

        vector<string> data = explode(vec[1], ';');

        for (auto v : data) {
            cout << v << endl;

            vector<string> handful = explode(v, ',');

            for (auto h : handful) {
                string numbers;

                for (string::iterator it = h.begin(); it != h.end(); it++) {
                    if (isdigit(*it)) {
                        numbers.push_back(*it);
                    } else if (numbers != "" && *it != ' ') {
                        int nums = stoi(numbers);

                        numbers = "";

                        if (h.find("red") != string::npos) {
                            maxRed = maxRed >= nums ? maxRed : nums;
                            cout << "maxRed: " << maxRed << endl;
                        } else if (h.find("green") != string::npos) {
                            maxGreen = maxGreen >= nums ? maxGreen : nums;
                            cout << "maxGreen: " << maxGreen << endl;
                        } else {
                            maxBlue = maxBlue >= nums ? maxBlue : nums;
                            cout << "maxBlue: " << maxBlue << endl;
                        }
                    }
                }

            }
        }

        if (maxRed <= RED && maxGreen <= GREEN && maxBlue <= BLUE) {
            sum += gameId;
        }
    }

    cout << sum << endl;
}

