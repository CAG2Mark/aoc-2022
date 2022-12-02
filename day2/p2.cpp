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
                case 'X': score += 3 + 0; break; // lose, scissors
                case 'Y': score += 1 + 3; break; // tie, rock
                case 'Z': score += 2 + 6; break; // win, paper
            }
        }
        // paper
        if (spl[0] == "B") {
            switch (spl[1][0]) {
                case 'X': score += 1 + 0; break; // lose, rock
                case 'Y': score += 2 + 3; break; // tie, paper
                case 'Z': score += 3 + 6; break; // win, scissors
            }
        }
        // scissors
        if (spl[0] == "C") {
            switch (spl[1][0]) {
                case 'X': score += 2 + 0; break; // lose, paper
                case 'Y': score += 3 + 3; break; // tie, scissors
                case 'Z': score += 1 + 6; break; // win, rock
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