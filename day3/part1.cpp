#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int getNumber(string::iterator it) {
    int sum = 0;

    while (isdigit(*it)) {
        it++;
    }

    it--;

    int power = 0;

    while (isdigit(*it)) {
        sum += (*it - 0x30) * pow(10, power);
        it--;
        power++;
    }

    cout << sum << endl;

    return sum;
}

int main(int argc, char* argv[]) {
    string input = "./input";

    if (argc > 1) input = argv[1];

    ifstream file(input);
    string prev = "";
    string runner;

    int sum = 0;

    while (getline(file, runner)) {
        if (prev != "") {
            string::iterator prevIt = prev.begin();
            string::iterator it = runner.begin();

            while (it != runner.end() && prevIt != runner.end()) {
                char prevChar = *prevIt;

                if (!isdigit(*it) && *it != '.') {
                    it--;

                    if (isdigit(*it)) {
                        sum += getNumber(it);
                        it++;
                        it++;
                    } else {
                        it++;
                        it++;
                    }

                    if (isdigit(*it)) {
                        sum += getNumber(it);
                    }

                    it--;

                    if (isdigit(*prevIt)) {
                        sum += getNumber(prevIt);
                    } else {
                        prevIt--;
                        if (isdigit(*prevIt)) {
                            sum += getNumber(prevIt);
                        }
                        prevIt++;
                        prevIt++;

                        if (isdigit(*prevIt)) {
                            sum += getNumber(prevIt);
                        }

                        prevIt--;
                    }
                }

                if (!isdigit(*prevIt) && *prevIt != '.') {
                    if (isdigit(*it)) {
                        sum += getNumber(it);
                    } else {
                        it--;

                        if (isdigit(*it)) {
                            sum += getNumber(it);
                        }
                        it++;
                        it++;

                        if (isdigit(*it)) {
                            sum += getNumber(it);
                        }

                        it--;
                    }
                }

                prevIt++;
                it++;
            }
        }

        prev = runner;
    }

    cout << sum << endl;
}
