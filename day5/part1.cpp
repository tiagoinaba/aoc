#include "../day4/thelib.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct Range {
    long destStart;
    long srcStart;
    long range;
};

int main(int argc, char* argv[]) {
    ifstream contents("./input");

    string line;

    vector<vector<Range>> relations;  

    getline(contents, line);

    vector<string> seedStr = explode(explode(line, ": ")[1], " ");

    vector<long> seeds;  

    for (const string& str : seedStr) {
        cout << str << endl;
        seeds.push_back(stol(str));
    }

    getline(contents, line);

    vector<Range> ranges;  

    vector<long> result;

    while (getline(contents, line)) {
        if (isdigit(line[0])) {
            vector<string> vals = explode(line, " ");
            Range rng;
            
            rng.destStart = stol(vals[0]);
            rng.srcStart = stol(vals[1]);
            rng.range = stol(vals[2]);

            ranges.push_back(rng);
        } else {
            if (ranges.size() > 0) {
                relations.push_back(ranges);
            }
            ranges = {};
        }
    }

    if (ranges.size() > 0) relations.push_back(ranges);

     for (long s = 0; s < seeds.size(); s++) {
        long cur = seeds[s];

        for (long i = 0; i < relations.size(); i++) {
            bool found = false;
            for (long j = 0; j < relations[i].size(); j++) {
                Range curRel = relations[i][j];


                if (cur >= curRel.srcStart && cur < curRel.srcStart + curRel.range && !found) {
                    cur += curRel.destStart - curRel.srcStart;
                    found = true;
                }
            }
        }
        result.push_back(cur);
        cout << "result: " << cur << endl; 
    }

     sort(result.begin(), result.end());

     for (auto res : result) {
         cout << res << endl;
     }
}
