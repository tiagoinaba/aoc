#include "../day4/thelib.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

ulong getLCM(ulong a, ulong b) {
    cout << "Checking: " << a << ' ' << b << '\n';

    ulong c = max(a, b);

    while (true) {
        if (c % a == 0 && c % b == 0) return c;
        else c += max(a, b);
    }
}

int main (int argc, char* argv[]) {
    ifstream contents("./input");
    string directions;
    getline(contents, directions);

    string line;

    map<string, pair<string, string>> myMap;
    vector<string> startingPos;

    while (getline(contents, line)) {
        if (line != "") {
            string key = explode(line, " = ")[0];
            string left = explode(explode(explode(line, " = ")[1], ", ")[0], "(")[0];
            string right = explode(explode(explode(line, " = ")[1], ", ")[1], ")")[0];

            myMap.insert({key, {left, right}});

            if (key[2] == 'A') startingPos.push_back({key});
        }
    }

    ulong result = 1;

    for (auto pos : startingPos) {
        ulong steps = 0;

        do {
            for (char dir : directions) {
                if (pos[2] == 'Z') {
                    break;
                }
                steps++;
                switch (dir) {
                    case 'L':
                        pos = myMap.at(pos).first;
                        break;
                    case 'R':
                        pos = myMap.at(pos).second;
                }
            }
        } while (pos[2] != 'Z');
        
        result = getLCM(result, steps);
        cout << "Result: " << result << '\n';
    }

    cout << result << '\n';
}
