#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y, z;

    int fill_iter = 0;

    int getHash() const { return x + 100 * y + 100000 * z; }
};

bool operator<(const Point &a, const Point &b) {
    return a.getHash() < b.getHash();
}

inline vector<Point> get_neighbours(int x, int y, int z) {
    return {
        { x - 1, y, z },
        { x + 1, y, z },
        { x, y - 1, z },
        { x, y + 1, z },
        { x, y, z - 1 },
        { x, y, z + 1 },
    };
}

int try_fill_hole(set<Point> &a, int x, int y, int z, int min_x, int max_x,
    int min_y, int max_y, int min_z, int max_z, int fill_iter) {
    int sa_diff = 0;

    vector<Point> st;
    st.push_back({ x, y, z, fill_iter });
    bool debug = false;
    if (x == 2 && y == 2 && z == 5) {
        debug = true;
    }

    bool leak = false;
    while (!st.empty()) {
        Point p = st.back();
        st.pop_back();

        if (a.find(p) != a.end()) {
            continue;
        }

        if (p.x < min_x || max_x <= p.x || p.y < min_y || max_y <= p.y
            || p.z < min_z || max_z <= p.z) {
            return 0;
        }

        a.insert(p);
        sa_diff += 6;

        vector<Point> neighbours = get_neighbours(p.x, p.y, p.z);
        for (Point &q : neighbours) {
            Point r;
            if (a.find(q) != a.end()) {
                r = *a.find(q);
                if (r.fill_iter != 0 && r.fill_iter != fill_iter) {
                    return 0;
                }
                sa_diff -= 2;
                continue;
            }
            q.fill_iter = fill_iter;
            st.push_back(q);
        }
    }

    if (leak)
        return 0;

    return sa_diff;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    set<Point> a;
    int sa = 0;

    int min_x = 10, max_x = 0, min_y = 10, max_y = 0, min_z = 10, max_z = 0;
    for (string ln : lns) {
        sa += 6;
        int x, y, z;
        vector<string> spl = split_str(ln, ",");
        x = stoi(spl[0]);
        y = stoi(spl[1]);
        z = stoi(spl[2]);

        min_x = min(x, min_x);
        max_x = max(x, max_x);
        min_y = min(y, min_y);
        max_y = max(y, max_y);
        min_z = min(z, min_z);
        max_z = max(z, max_z);

        // check neighbours
        vector<Point> to_check = get_neighbours(x, y, z);

        a.insert({ x, y, z, 0 });

        for (const Point &p : to_check) {
            if (a.find(p) != a.end()) {
                sa -= 2;
            }
        }
    }
    int iter = 0;

    for (int x = min_x; x <= max_x; ++x) {
        for (int y = min_y; y <= max_y; ++y) {
            for (int z = min_z; z <= max_z; ++z) {
                if (a.find({ x, y, z }) != a.end())
                    continue;

                sa += try_fill_hole(a, x, y, z, min_x, max_x, min_y, max_y,
                    min_z, max_z, ++iter);
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