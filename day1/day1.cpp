#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <string>

using namespace std;

map<string, int> digs = {
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

int getLineNum(string line) {
    int sum = 0;

    for (string::iterator it = line.begin(); it != line.end(); it++) {
        if (isdigit(*it)) {
            sum += (*it - 48) * 10;
            break;
        }
    }

    for (string::reverse_iterator it = line.rbegin(); it != line.rend(); it++) {
        if (isdigit(*it)) {
            sum += *it - 48;
            break;
        }
    }

    return sum;
}

int getLineNumSpelledOut(string line) {
    int sum = 0;
    string buf = "";
    bool found = false;

    string::iterator it = line.begin();

    while(it != line.end() && !found) {
        if (isdigit(*it)) {
            sum += (*it - 48) * 10;
            break;
        } else {
            buf.push_back(*it);

            if (buf.size() >= 3) {
                for (map<string, int>::iterator digsIt = digs.begin(); digsIt != digs.end(); digsIt++) {
                    if (buf.find(digsIt->first) != string::npos) {
                        sum += digsIt->second * 10;
                        found = true;
                        break;
                    }
                }
            }
        }

        it++;
    }


    buf = "";
    found = false;

    string::reverse_iterator rIt = line.rbegin();

    while (rIt != line.rend() && !found) {
        if (isdigit(*rIt)) {
            sum += *rIt - 48;
            break;
        } else {
            buf.insert(0, 1, *rIt);

            if (buf.size() >= 3) {
                for (map<string, int>::iterator digsIt = digs.begin(); digsIt != digs.end(); digsIt++) {
                    if (buf.find(digsIt->first) != string::npos) {
                        sum += digsIt->second;
                        found = true;
                        break;
                    }
                }
            }
        }

        rIt++;
    }

    return sum;
}

int main(int argc, char* argv[]) {
    ifstream input("input");
    string line;

    int sum = 0;

    /*

    while (getline(input, line)) {
        sum += getLineNum(line);
    } */

    while (getline(input, line)) {
        sum += getLineNumSpelledOut(line);
    }

    cout << sum << endl;
}
