#include "thelib.h"

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
