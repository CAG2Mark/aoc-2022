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

void perform_move(int dir, array<int, 10> &x, array<int, 10> &y, set<long long> &points) {
    int &hx = x[0];
    int &hy = y[0];

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

    for (int i = 1; i < 10; ++i) {
        int px = x[i-1];
        int py = y[i-1];

        int &tx = x[i], &ty = y[i];

        int dx = px - tx;
        int dy = py - ty;

        if (i == 9)
            points.insert(to_hash(tx, ty));

        if (abs(dx) <= 1 && abs(dy) <= 1) continue;

        tx += sgn(dx);
        ty += sgn(dy);
    }
}

void solve(string filename) {
    set<long long> points;
    array<int, 10> x = {0};
    array<int, 10> y = {0};

    vector<string> lns = get_lines(filename);
    for (string ln : lns) {
        vector<string> split = split_str(ln, " ");
        char dir = split[0][0];
        int move = stoi(split[1]);

        for (int i = 0; i < move; ++i)
            perform_move(dir, x, y, points);

        cout << x[9] << " " << y[9] << "\n";
    }

    points.insert(to_hash(x[9], y[9]));

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