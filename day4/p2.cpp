#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

void solve() {
    vector<string> lns = get_lines();

    int sum = 0;
    for (string ln : lns) {
        vector<string> split = split_str(ln, ",");
        vector<string> spl1 = split_str(split[0], "-");
        vector<string> spl2 = split_str(split[1], "-");

        int a1 = stoi(spl1[0]);
        int a2 = stoi(spl1[1]);
        int b1 = stoi(spl2[0]);
        int b2 = stoi(spl2[1]);

        vector<int> cheating(max(a2, b2) + 1,0);
        for (int i = a1; i <= a2; ++i) {
            cheating[i] = 1;
        }
        for (int i = b1; i <= b2; ++i) {
            if (cheating[i]) {
                ++sum;
                break;
            }
        }

    }

    cout << sum << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}