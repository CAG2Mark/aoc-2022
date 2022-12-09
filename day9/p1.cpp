#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

long long to_hash(int x, int y) {
    return x*69420 + y;
}

int sgn(int x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}

void perform_move(int dir, int &tx, int &ty, int &hx, int &hy, set<long long> &points) {
    switch (dir) {
    case 'U':
        ++hy;
        break;
    case 'D':
        --hy;
        break;
    case 'R':
        ++hx;
        break;
    case 'L':
        --hx;
        break;
    }

    int dx = hx - tx;
    int dy = hy - ty;

    points.insert(to_hash(tx, ty));

    if (abs(dx) <= 1 && abs(dy) <= 1) return;

    tx += sgn(dx);
    ty += sgn(dy);
    
}

void solve(string filename) {
    int tx = 0, ty = 0, hx = 0, hy = 0;
    set<long long> points;

    vector<string> lns = get_lines(filename);
    for (string ln : lns) {
        vector<string> split = split_str(ln, " ");
        char dir = split[0][0];
        int move = stoi(split[1]);

        for (int i = 0; i < move; ++i)
            perform_move(dir, tx, ty, hx, hy, points);
    }

    points.insert(to_hash(tx, ty));

    cout << points.size() << "\n";
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