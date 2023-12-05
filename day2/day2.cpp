#include <string>
#include <vector>

using namespace std;

vector<string> explode(const string& str, const char& sep) {
    string buf;
    vector<string> result;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] != sep) {
            buf.push_back(str[i]);
        } else if(str[i] == sep && buf != "") {
            result.push_back(buf);
            buf = "";
        }
    }

    if (buf != "") {
        result.push_back(buf);
    }

    return result;
}
