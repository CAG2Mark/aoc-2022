#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

void solve() {
    vector<string> lns = get_lines();
    string ln = lns[0];
    for (int i = 0; i < ln.size() - 14; ++i) {
        vector<char> a;
        bool flag = false;
        for (int j = 0; j < 14; ++j) {
            for (char c : a) {
                if (c == ln[i +j]) {
                    flag = true;
                    break;
                }
            }
            if (flag) break;
            a.push_back(ln[i + j]);
        }

        if (!flag) {
            cout << i + 14 << "\n";
            break;
        }
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}