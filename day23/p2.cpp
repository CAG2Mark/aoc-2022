#include "../utils/aocutils.h"
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct Tile {
    bool empty = true;
};

void print_map(deque<deque<Tile>> &map) {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            cout << (map[i][j].empty ? '.' : '#');
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<tuple<int, int>> to_points(int row, int col, int dir) {
    switch (dir) {
    case 0:
        return { { row - 1, col - 1 }, { row - 1, col }, { row - 1, col + 1 } };
    case 1:
        return { { row - 1, col + 1 }, { row, col + 1 }, { row + 1, col + 1 } };
    case 2:
        return { { row + 1, col - 1 }, { row + 1, col }, { row + 1, col + 1 } };
    case 3:
        return { { row - 1, col - 1 }, { row, col - 1 }, { row + 1, col - 1 } };
    }
    return {};
}

const int DIRS[] = { 0, 2, 3, 1 };

bool trim_map(deque<deque<Tile>> &map) {
    bool changed = false;

    bool flag;

    flag = true;
    for (auto t : map.front()) {
        if (t.empty) 
            continue;
        
        flag = false;
        break;
    }

    if (flag) {
        map.pop_front();
        changed = true;
    }

    flag = true;
    for (auto t : map.back()) {
        if (t.empty)
            continue;

        flag = false;
        break;
    }

    if (flag) {
        map.pop_back();
        changed = true;
    }

    flag = true;
    for (const auto &row : map) {
        if (row.front().empty)
            continue;

        flag = false;
        break;
    }

    if (flag) {
        for (auto &row : map)
            row.pop_front();
        changed = true;
    }

    flag = true;
    for (const auto &row : map) {
        if (row.back().empty)
            continue;

        flag = false;
        break;
    }

    if (flag) {
        for (auto &row : map)
            row.pop_back();
        changed = true;
    }
    return changed;
}

bool advance_map(deque<deque<Tile>> &map, int iter) {
    bool changed = false;

    for (int i = 0; i < map.size(); ++i) {
        deque<Tile> &row = map[i];
        row.push_back(Tile());
        row.push_front(Tile());
    }
    int COLS = map[0].size();
    map.push_back(deque<Tile>(COLS, Tile()));
    map.push_front(deque<Tile>(COLS, Tile()));

    int ROWS = map.size();

    vector<vector<tuple<int, int>>> proposed(ROWS, vector<tuple<int, int>>());
    for (auto &v : proposed) {
        for (int i = 0; i < COLS; ++i)
            v.push_back({ -1, -1 });
    }

    for (int i = 1; i < ROWS - 1; ++i) {
        deque<Tile> &row = map[i];
        for (int j = 1; j < COLS - 1; ++j) {
            Tile &a = row[j];
            if (a.empty)
                continue;

            bool flag_ = false;
            // check surrounding
            for (int p = i - 1; p < i + 2; ++p) {
                for (int q = j - 1; q < j + 2; ++q) {
                    if (p == i && q == j) continue;

                    if (map[p][q].empty) continue;
                    flag_ = true;
                    break;
                }
            }

            if (!flag_) continue;

            changed = true;

            for (int k = 0; k < 4; ++k) {
                int dir = DIRS[(k + iter) % 4];
                auto &&p = to_points(i, j, dir);

                auto [dest_row, dest_col] = p[1];

                bool flag = true;
                for (auto [a, b] : p) {
                    if (!map[a][b].empty) {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    continue;

                // confirmed can move, propose move

                auto [d, e] = proposed[dest_row][dest_col];
                if (d != -1) {
                    proposed[dest_row][dest_col] = { -2, -2 };
                    break;
                }

                proposed[dest_row][dest_col] = { i, j };

                break;
            }
        }
    }

    if (!changed) return changed;

    for (int i = 0; i < ROWS; ++i) {
        const vector<tuple<int, int>> &row = proposed[i];
        for (int j = 0; j < COLS; ++j) {
            auto [a, b] = row[j];
            if (a < 0)
                continue;

            // move tile
            map[i][j] = map[a][b];
            Tile &t = map[i][j];

            map[a][b] = Tile();
        }
    }

    bool t = true;
    while (t) {
        t = trim_map(map);
    }

    return changed;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);
    deque<deque<Tile>> map;
    for (string ln : lns) {
        map.push_back(deque<Tile>());
        for (char c : ln) {
            Tile t;
            t.empty = c != '#';
            map.back().push_back(t);
        }
    }

    for (int i = 0; i < 10000; ++i) {
        bool t = advance_map(map, i);
        if (!t) {
            cout << i+1 << "\n";
            break;
        }
        // print_map(map);
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