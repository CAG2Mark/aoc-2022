#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y, z;

    int getHash() const { return x + 100 * y + 100000 * z; }
};

bool operator<(const Point &a, const Point &b) {
    return a.getHash() < b.getHash();
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    set<Point> a;
    int sa = 0;
    for (string ln : lns) {
        sa += 6;
        int x, y, z;
        vector<string> spl = split_str(ln, ",");
        x = stoi(spl[0]);
        y = stoi(spl[1]);
        z = stoi(spl[2]);

        // check neighbours
        vector<Point> to_check = {
            { x - 1, y, z },
            { x + 1, y, z },
            { x, y - 1, z },
            { x, y + 1, z },
            { x, y, z - 1 },
            { x, y, z + 1 },
        };

        a.insert({ x, y, z });

        for (const Point &p : to_check) {
            if (a.find(p) != a.end()) {
                sa -= 2;
            }
        }
    }

    cout << sa << "\n";
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