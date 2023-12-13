#include "../day4/thelib.h"
#include <algorithm>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <utility>
#include <variant>
#include <vector>

vector<char> CARDCHARS = { 
    'A',
    'K',
    'Q',
    'T',
    '9',
    '8',
    '7',
    '6',
    '5',
    '4',
    '3',
    '2',
    'J'
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
        auto itA = find_if(CARDCHARS.begin(), CARDCHARS.end(), [a, i](const char& c) {
                return a.cards[i] == c;
                });
        auto itB = find_if(CARDCHARS.begin(), CARDCHARS.end(), [b, i](const char& c) {
                return b.cards[i] == c;
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

        for (int i = 0; i < groups.size(); i++) {
            if (groups[i].first == card) {
                inGroups = true;
                groups[i].second++;
                break;
            }
        }

        if (!inGroups) groups.push_back({card, 1});
    }

    const auto joker = find_if(groups.begin(), groups.end(), [](const pair<char, int>& cur) {
                return cur.first == 'J';
            });

    if (joker != groups.end() && joker->second != 5) {
        int add = joker->second;
        groups.erase(joker);
        sort(groups.begin(), groups.end(), [](const pair<char, int> &a, const pair<char, int> &b) { 
                if (a.second != b.second)
                    return a.second > b.second;

                auto itA = find_if(CARDCHARS.begin(), CARDCHARS.end(), [a](const char& c) {
                        return a.first == c;
                        });
                auto itB = find_if(CARDCHARS.begin(), CARDCHARS.end(), [b](const char& c) {
                        return b.first == c;
                        });

                return itA > itB ? true : false;
                });

        //cout << "First: " << groups[0].first << ", " << groups[0].second << '\n';
        //cout << "Sum: " << add + groups[0].second << '\n';
        groups[0].second += add;
        //cout << groups[0].first << ' ' << groups[0].second << '\n';
    }

    bool trio = false;
    int pairs = 0;
    int singles = 0;

    for (auto group : groups) {

        //cout << group.first << group.second << '\n';
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
        string type;
        switch (hand.type) {
            case HIGH_CARD:
                type = "High Card";
                break;
            case ONE_PAIR:
                type = "One Pair";
                break;
            case TWO_PAIR:
                type = "Two Pair";
                break;
            case THREE_OF_A_KIND:
                type = "Three of a Kind";
                break;
            case FULL_HOUSE:
                type = "Full house";
                break;
            case FOUR_OF_A_KIND:
                type = "Four of a Kind";
                break;
            case FIVE_OF_A_KIND:
                type = "Five of a Kind";
                break;
        }
        //cout << "Rank: " << rank << '\n';
        result += hand.bid * rank;
        rank++;
    }

    cout << result << '\n';
}
