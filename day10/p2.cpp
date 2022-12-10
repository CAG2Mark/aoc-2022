#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

void cycle(int &cyclecnt, int &X, int add, array<int, 240> &crt) { 
    X += add;

    if (X - 1 <= cyclecnt % 40 && cyclecnt % 40 <= X+1) {
        crt[cyclecnt] = 1;
    }
    ++cyclecnt;
}

void solve(string filename) {
    int cyclecnt = 1, X = 1, sum = 0;

    array<int, 240> crt = {0};

    vector<string> lns = get_lines(filename);
    for (string ln : lns) {
        if (ln[0] == 'a') {
            vector<string> split = split_str(ln, " ");
            int add = stoi(split[1]);
            
            cycle(cyclecnt, X, 0, crt);
            cycle(cyclecnt, X, add, crt);
        }
        else {
            cycle(cyclecnt, X, 0, crt);
        }
    }

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 40; ++j) {
            int pos = i*40 + j;
            cout << (crt[pos] ? '#' : '.');
        }
        cout << '\n';
    }
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