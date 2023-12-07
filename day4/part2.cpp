#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

vector<string> explode(string str, string sep) {
    vector<string> res{};

    while (true) {
        long found = str.find(sep);

        if (found == string::npos) {
            break;
        } else {
            if (str.substr(0, found) != "")
                res.push_back(str.substr(0, found));
            str.erase(0, found + sep.length());
        }
    }

    if (str != "") {
        res.push_back(str);
    }

    return res;
}

bool findInSortedVec(vector<string> vec, string toFind) {
    long half = vec.size() / 2;

    if (half == 0 && vec[half] != toFind) return false;

    if (vec[half] == toFind) return true;
    else if (vec[half] > toFind) {
        vector<string> firstHalf(vec.begin(), vec.begin() + half);
        return findInSortedVec(firstHalf, toFind);
    } else {
        vector<string> secondHalf(vec.begin() + half, vec.end());
        return findInSortedVec(secondHalf, toFind);
    } 
}

int main(int argc, char* argv[]) {
    ifstream contents("./input");
    string line;

    map<int, int> cardsCopies = {};

    int pileSum = 0;

    while (getline(contents, line)) {
        int gameNumber = stoi(explode(explode(line, ": ")[0], " ")[1]);
        cout << gameNumber << endl;
        vector<string> left = explode(explode( explode(line, ": ")[1], " | " )[0], " ");
        vector<string> right = explode(explode( explode(line, ": ")[1], " | " )[1], " ");

        // how many numbers we got right
        int cardValue = 0;

        sort(left.begin(), left.end());
        sort(right.begin(), right.end());

        for (int i = 0; i < left.size(); i++) {
            bool found = findInSortedVec(right, left[i]);
            if (found) cardValue++;
        }

        if (cardValue > 0) {
            // look for this card in the map
            map<int, int>::iterator cur = cardsCopies.find(gameNumber);

            // amount of copies I have of this card (including the original);
            int copies = 1;

            // add the copies in the map
            if (cur != cardsCopies.end()) {
                copies += cur->second;
            }

            pileSum += cardValue * copies;

            // starting from after the current card, add the values to the map
            for (int i = 1; i <= cardValue; i++) {
                map<int, int>::iterator found = cardsCopies.find(gameNumber + i);

                // if inserted, add the copies to it, else insert it with the number of copies
                if (found != cardsCopies.end()) {
                    found->second += copies;
                } else {
                    cardsCopies.insert({gameNumber + i, copies});
                }
            }
        } 

        pileSum++;
    }

    cout << "result: " << pileSum << endl;
}
