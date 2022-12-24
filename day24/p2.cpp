#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <iterator>

using namespace std;

// blizzards represented using int as dirs, 0 = up
struct Tile {
    vector<int> blizzards;

    bool safe() const { return blizzards.empty(); }
};

vector<vector<Tile>> advance(const vector<vector<Tile>> &map) {
    int ROWS = map.size();
    int COLS = map[0].size();

    vector<vector<Tile>> ret(ROWS, vector<Tile>(COLS, Tile()));

    for (int i = 0; i < ROWS; ++i) {
        const vector<Tile> &row = map[i];
        for (int j = 0; j < COLS; ++j) {
            const Tile &t = row[j];

            for (int blizzard : t.blizzards) {
                int n_row = i, n_col = j;
                switch (blizzard) {
                case 0:
                    --n_row;
                    break;
                case 1:
                    ++n_col;
                    break;
                case 2:
                    ++n_row;
                    break;
                case 3:
                    --n_col;
                    break;
                }

                n_row = (n_row + ROWS) % ROWS;
                n_col = (n_col + COLS) % COLS;

                ret[n_row][n_col].blizzards.push_back(blizzard);
            }
        }
    }
    return ret;
}

const int delta[5][2] = { { 0, 0 }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

vector<tuple<int, int>> neighbours(
    const vector<vector<Tile>> &map, const tuple<int, int> &pos) {
    int ROWS = map.size();
    int COLS = map[0].size();

    auto [i, j] = pos;
    vector<tuple<int, int>> ret;
    for (int p = 0; p < 5; ++p) {
        int new_i = i + delta[p][0];
        int new_j = j + delta[p][1];

        if (new_i < 0 || new_i >= ROWS || new_j < 0 || new_j >= COLS)
            continue;

        if (!map[new_i][new_j].safe())
            continue;

        ret.push_back({ new_i, new_j });
    }
    return ret;
}

void print_map(const vector<vector<Tile>> &map, int r = -1, int c = -1) {
    char a[4] = { '^', '>', 'v', '<' };
    for (int i = 0; i < map.size(); ++i) {
        const auto &row = map[i];
        for (int j = 0; j < row.size(); ++j) {
            auto t = row[j];

            if (i == r && j == c)
                cout << 'E';
            else if (t.safe())
                cout << ".";
            else if (t.blizzards.size() == 1) {
                cout << a[t.blizzards[0]];
            } else if (t.blizzards.size() <= 9) {
                cout << t.blizzards.size();
            } else {
                cout << 'X';
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int bfs(const vector<vector<vector<Tile>>> &maps, int initial_wait,
    tuple<int, int> start, tuple<int, int> dest, int best = 2000) {
    int ROWS = maps[0].size();
    int COLS = maps[0][0].size();

    set<tuple<int, int>> cur = { start };

    for (int i = 0; i < best; ++i) {
        const vector<vector<Tile>> &map =
            maps[(i + initial_wait) % maps.size()];

        set<tuple<int, int>> next = {};

        for (auto &p : cur) {
            auto n = neighbours(map, p);
            for (auto &q : n) {
                if (q == dest)
                    return i;
                next.insert(q);
            }
        }

        if (next.size() == 0)
            return -100000000;

        // cout << iters << '\n';
        // cout << cur.size() << "\n";
        cur = next;
    }
    return -100000000;
}

int get_best(const vector<vector<vector<Tile>>> &maps, tuple<int, int> start, tuple<int, int> dest, int start_wait) {
    int ROWS = maps[0].size();
    int COLS = maps[0][0].size();

    vector<int> ret;

    int m = 2000;
    int best_start = -1;
    for (int i = 0; i < maps.size(); ++i) {
        // cout << "WAIT " << i << "\n";
        int a = bfs(maps, i + start_wait, start, dest, m - i - 1) + i + 1;
        if (a < 0) 
            continue;
        if (a < m) {
            m = a;
            best_start = i;
        }
    }
    return m;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);
    vector<vector<Tile>> map;

    for (int i = 1; i < lns.size() - 1; ++i) {
        map.push_back(vector<Tile>());
        for (int j = 1; j < lns[i].size() - 1; ++j) {
            vector<Tile> &row = map.back();
            row.push_back(Tile());
            switch (lns[i][j]) {
            case '^':
                row.back().blizzards.push_back(0);
                break;
            case '>':
                row.back().blizzards.push_back(1);
                break;
            case 'v':
                row.back().blizzards.push_back(2);
                break;
            case '<':
                row.back().blizzards.push_back(3);
                break;
            }
        }
    }

    int ROWS = map.size();
    int COLS = map[0].size();

    int iters = ROWS * COLS / gcd(ROWS, COLS);

    vector<vector<vector<Tile>>> maps;
    for (int i = 0; i < iters; ++i) {
        maps.push_back(map);
        map = advance(map);
    }

    int b1 = get_best(maps, {-1, 0}, {ROWS - 1, COLS - 1}, 0);
    // b1 %= iters;
    cout << b1  << "\n";

    int b2 = get_best(maps, {ROWS, COLS - 1}, {0, 0}, (b1) % iters);

    cout << b2 << "\n";

    int b3 = get_best(maps, {-1, 0}, {ROWS - 1, COLS - 1}, (b1 + b2) % iters);

    cout << b3 << "\n";

    cout << b1 + b2 + b3 << "\n";
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