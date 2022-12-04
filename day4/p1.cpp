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
        if (a1 <= b1 && a2 >= b2) ++sum;
        else if (b1 <= a1 && a2 <= b2) ++sum;
    }

    cout << sum << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}