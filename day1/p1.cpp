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

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    vector<string> lns = get_lines();
    
}