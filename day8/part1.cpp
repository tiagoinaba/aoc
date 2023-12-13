#include "../day4/thelib.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

int main (int argc, char* argv[]) {
    ifstream contents("./input");
    string directions;
    getline(contents, directions);

    string line;

    map<string, pair<string, string>> myMap;

    while (getline(contents, line)) {
        if (line != "") {
            string key = explode(line, " = ")[0];
            string left = explode(explode(explode(line, " = ")[1], ", ")[0], "(")[0];
            string right = explode(explode(explode(line, " = ")[1], ", ")[1], ")")[0];

            myMap.insert({key, {left, right}});
        }
    }

    string pos = myMap.begin()->first;

    int steps = 0;

    while (pos != "ZZZ") {
        for (char dir : directions) {
            steps++;
            if (pos == "ZZZ")
                break;
            switch (dir) {
                case 'L':
                    pos = myMap.at(pos).first;
                    break;
                case 'R':
                    pos = myMap.at(pos).second;
            }
        }
    }

    cout << steps << '\n';
}
