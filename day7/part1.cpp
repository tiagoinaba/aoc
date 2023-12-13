#include "../day4/thelib.h"
#include <algorithm>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <utility>
#include <vector>

vector<pair<char, int>> CARDCHARS = { 
    { 'A', 13 },
    { 'K', 12 },
    { 'Q', 11 },
    { 'J', 10 },
    { 'T', 9 },
    { '9', 8 },
    { '8', 7 },
    { '7', 6 },
    { '6', 5 },
    { '5', 4 },
    { '4', 3 },
    { '3', 2 },
    { '2', 1 }
};

enum HandTypes {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

struct Hand {
    string cards;
    int bid;
    HandTypes type;
};

bool rankHands(const Hand& a, const Hand& b) {
    if (a.type != b.type)
        return a.type < b.type;

    for (int i = 0; i < 5; i++) {
        auto itA = find_if(CARDCHARS.begin(), CARDCHARS.end(), [a, i](const pair<char, int>& c) {
                return a.cards[i] == c.first;
                });
        auto itB = find_if(CARDCHARS.begin(), CARDCHARS.end(), [b, i](const pair<char, int>& c) {
                return b.cards[i] == c.first;
                });

        if (itA != itB) {
            return itA > itB ? true : false;
        }
    }
    
    return false;
}

HandTypes getHandType(string cards) {
    vector<pair<char, int>> groups;

    for (auto card : cards) {
        bool inGroups = false;

        for (int i = 0; i < groups.size() ; i++) {
            if (groups[i].first == card) {
                inGroups = true;
                groups[i].second++;
                break;
            }
        }

        if (!inGroups) groups.push_back({card, 1});
    }

    bool trio = false;
    int pairs = 0;
    int singles = 0;

    for (auto group : groups) {
        if (group.second == 5) return FIVE_OF_A_KIND;
        if (group.second == 4) return FOUR_OF_A_KIND;
        if (group.second == 3) trio = true;
        if (group.second == 2) pairs++;
        if (group.second == 1) singles++;
    }

    if (trio) {
        return pairs > 0 ? FULL_HOUSE : THREE_OF_A_KIND;
    }

    if (pairs > 0) {
        return pairs == 1 ? ONE_PAIR : TWO_PAIR;
    }

    return HIGH_CARD;
}

int main(int argc, char* argv[]) {
    ifstream content("./input");
    string line;

    vector<Hand> hands;

    while (getline(content, line)) {
        string cards = explode(line, " ")[0];
        Hand newHand;
        newHand.cards = cards;
        newHand.bid = stoi(explode(line, " ")[1]);
        newHand.type = getHandType(cards);
        hands.push_back(newHand);
    }

    sort(hands.begin(), hands.end(), rankHands);

    int result = 0;
    int rank = 1;

    for (auto hand : hands) {
        result += hand.bid * rank;
        rank++;
    }

    cout << result << '\n';
}
