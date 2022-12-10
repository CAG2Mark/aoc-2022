#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

const int CHECK[] = {20, 60, 100, 140, 180, 220};

void cycle(int &cyclecnt, int &X, int &sum, int add = 0) {
    ++cyclecnt;
    X += add;

    for (int i = 0; i < 6; ++i) {
        if (CHECK[i] == cyclecnt) {
            sum += cyclecnt * X;
            break;
        }
    }
}

void solve(string filename) {
    int cyclecnt = 1, X = 1, sum = 0;
    
    vector<string> lns = get_lines(filename);
    for (string ln : lns) {
        if (ln[0] == 'a') {
            vector<string> split = split_str(ln, " ");
            int add = stoi(split[1]);
            
            cycle(cyclecnt, X, sum);
            cycle(cyclecnt, X, sum, add);
        }
        else {
            cycle(cyclecnt, X, sum);;
        }
    }

    cout << sum << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    if (ifstream("input.test")) {
        cout << "TEST INPUT OUTPUT\n---------------------\n";
        solve("input.test");
        cout << "\n";
    }
    cout << "OUTPUT\n---------------------\n";
    solve("input");
}