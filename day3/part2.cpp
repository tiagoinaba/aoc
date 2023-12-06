#include <cstddef>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

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

    return sum;
}

struct Gear  {
    long index;
    int first;
    int second;
};

int main(int argc, char* argv[]) {

    string input = "./input";

    if (argc > 1) input = argv[1];

    ifstream file(input);

    string prev = "";
    string runner = "";
    string next = "";

    int sum = 0;


    while (getline(file, next)) {
        int first = 0;
        int second = 0;

        if (prev != "" && runner != "") {
            string::iterator prevIt = prev.begin();
            string::iterator it = runner.begin();
            string::iterator nextIt = next.begin();

            while (it != runner.end() && prevIt != prev.end() && nextIt != next.end()) {
                if (*it == '*') {
                    it--;

                    if (isdigit(*it)) {
                        first = getNumber(it);
                    }

                    it++;
                    it++;

                    if (isdigit(*it)) {
                        if (first == 0) 
                            first = getNumber(it);
                        else
                            second = getNumber(it);
                    }

                    it--;

                    if (isdigit(*prevIt)) {
                        if (first == 0) 
                            first = getNumber(prevIt);
                        else
                            second = getNumber(prevIt);
                    } else {
                        prevIt--;

                        if (isdigit(*prevIt)) {
                            if (first == 0) 
                                first = getNumber(prevIt);
                            else
                                second = getNumber(prevIt);
                        }

                        prevIt++;
                        prevIt++;

                        if (isdigit(*prevIt)) {
                            if (first == 0) 
                                first = getNumber(prevIt);
                            else
                                second = getNumber(prevIt);
                        }

                        prevIt--;
                    }

                    if (isdigit(*nextIt)) {
                        if (first == 0) 
                            first = getNumber(nextIt);
                        else
                            second = getNumber(nextIt);
                    } else {
                        nextIt--;

                        if (isdigit(*nextIt)) {
                            if (first == 0) 
                                first = getNumber(nextIt);
                            else
                                second = getNumber(nextIt);
                        }

                        nextIt++;
                        nextIt++;

                        if (isdigit(*nextIt)) {
                            if (first == 0) 
                                first = getNumber(nextIt);
                            else
                                second = getNumber(nextIt);
                        }

                        nextIt--;
                    }

                    if (first && second) {
                        sum += first * second;
                    }
                }

                first = 0;
                second = 0;

                prevIt++;
                it++;
                nextIt++;
            }
        }

        prev = runner;
        runner = next;
    }

    cout << sum << endl;
}
