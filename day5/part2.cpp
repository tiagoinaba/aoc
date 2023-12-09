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

struct SeedRange {
    long start;
    long end;
};

void printSeedRanges(vector<SeedRange> sr) {
    for (auto range : sr) {
        cout << "{ start: " << range.start << ", end: " << range.end << " }\n";
    }
}

int main(int argc, char* argv[]) {
    ifstream contents("./input");

    string line;

    vector<vector<Range>> relations;  

    getline(contents, line);

    vector<string> seedStr = explode(explode(line, ": ")[1], " ");

    vector<SeedRange> seeds;  

    for (vector<string>::iterator it = seedStr.begin(); it != seedStr.end(); it++) {
        SeedRange r;
        r.start = stol(*it);
        it++;
        r.end = r.start + stol(*it);

        seeds.push_back(r);
    }

    getline(contents, line);

    vector<Range> ranges;  

    vector<SeedRange> result;

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

    for (auto block : relations) {
        vector<SeedRange> next;

        while (seeds.size() > 0) {
            SeedRange cur = seeds.back();
            seeds.pop_back();
            bool found = false;

            for (auto r : block) {
                long overlapStart = cur.start > r.srcStart ? cur.start : r.srcStart;
                long overlapEnd = cur.end < r.srcStart + r.range ? cur.end : r.srcStart + r.range;

                if (overlapStart < overlapEnd) {
                    next.push_back({overlapStart + (r.destStart - r.srcStart), overlapEnd + (r.destStart - r.srcStart)});

                    if (overlapStart > cur.start) {
                        seeds.push_back({cur.start, overlapStart});
                    }

                    if (cur.end > overlapEnd) {
                        seeds.push_back({overlapEnd, cur.end});
                    }

                    found = true;
                    break;
                }
            }

            if (!found) next.push_back(cur);
        }

        seeds = next;
    }

    sort(seeds.begin(), seeds.end(), [](const SeedRange& a, const SeedRange& b) { return a.start < b.start; });

    cout << seeds[0].start << '\n';
}
