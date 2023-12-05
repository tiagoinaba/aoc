#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <variant>
#include <vector>
#include "day2.h"

using namespace std;

int main(int argc, char *argv[]) {
    string inputFile = "./input2";

    if (argc > 1) {
        inputFile = argv[1];
    }

    ifstream file(inputFile);
    string line;

    int sum = 0;

    while (getline(file, line)) {
        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        cout << "===================" << endl;
        vector<string> ex = explode(line, ':');

        vector<string> data = explode(ex[1], ';');

        for (int i = 0; i < data.size(); i++) {
            vector<string> color = explode(data[i], ',');

            for (int j = 0; j < color.size(); j++) {
                cout << color[j] << endl;

                string numBuf = "";

                for (string::iterator it = color[j].begin(); it != color[j].end(); it++) {
                    if (isdigit(*it)) {
                        numBuf.push_back(*it);
                    } else if (numBuf != "") {
                        cout << numBuf << endl;
                        int num = stoi(numBuf);
                        numBuf = "";

                        if (color[j].find("red") != string::npos) {
                            maxRed = maxRed > num ? maxRed : num;
                        }
                        if (color[j].find("green") != string::npos) {
                            maxGreen = maxGreen > num ? maxGreen : num;
                        }
                        if (color[j].find("blue") != string::npos) {
                            maxBlue = maxBlue > num ? maxBlue : num;
                        }
                    }
                }
            }
        }

        sum += maxRed * maxGreen * maxBlue;
    }

    cout << sum << endl;
}
