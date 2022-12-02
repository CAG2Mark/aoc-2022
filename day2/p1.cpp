#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

void solve() {
    vector<string> lns = get_lines();
    int score = 0;
    for (string ln : lns) {
        vector<string> spl = split_str(ln, " ");
        // rock
        if (spl[0] == "A") {
            switch (spl[1][0]) {
                case 'X': score += 1 + 3; break;
                case 'Y': score += 2 + 6; break;
                case 'Z': score += 3 + 0; break;
            }
        }
        // paper
        if (spl[0] == "B") {
            switch (spl[1][0]) {
                case 'X': score += 1 + 0; break;
                case 'Y': score += 2 + 3; break;
                case 'Z': score += 3 + 6; break;
            }
        }
        // scissors
        if (spl[0] == "C") {
            switch (spl[1][0]) {
                case 'X': score += 1 + 6; break;
                case 'Y': score += 2 + 0; break;
                case 'Z': score += 3 + 3; break;
            }
        }
    }

    cout << score << '\n';
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
    
}