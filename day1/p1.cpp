#include <bits/stdc++.h>
using namespace std;

vector<string> get_lines() {
    ifstream f("input");
    string line;

    vector<string> ret;
    
    while (getline(f, line)) {
        ret.push_back(line);
    }

    return ret;
}

string strip_str(string str) {
    int i = 0;
    int j = str.length() - 1;
    for (; i < str.length() && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'); ++i);
    for (; j >= 0 && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'); --j);

    return str.substr(i, j - i + 1);
}

bool string_is_whitespace(string str) {
    return strip_str(str).length() == 0;
}

vector<string> split_str(string inp, string delim, bool ignore_empty = false) {
    vector<string> ret;

    int pos = 0;
    while (pos < inp.length()) {
        string token = inp.substr(pos, inp.find(delim, pos) - pos);
        
        if (!ignore_empty || !string_is_whitespace(token))
            ret.push_back(token);
        
        pos += token.length() + delim.length();
    }
    return ret;
}

void solve() {
    vector<string> lns = get_lines();
    int sum = 0;
    int max = 0;
    for (string ln : lns) {
        if (string_is_whitespace(ln)) {
            if (sum > max) {
                max = sum;
            }
            sum = 0;
        } else {
            sum += stoi(ln);
        }
    }
    cout << max << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}