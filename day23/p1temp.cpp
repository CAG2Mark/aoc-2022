#include "../utils/aocutils.h"
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct Tile {
    bool empty = true;
    vector<int> dirs = {0, 2, 3, 1 };
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

deque<deque<Tile>> advance_map(deque<deque<Tile>> &map, int iter) {
    for (int i = 0; i < map.size(); ++i) {
        deque<Tile> &row = map[i];
        row.push_back(Tile());
        row.push_front(Tile());
    }
    int COLS = map[0].size();
    map.push_back(deque<Tile>(COLS, Tile()));
    map.push_front(deque<Tile>(COLS, Tile()));

    int ROWS = map.size();

    deque<deque<Tile>> out = map;

    print_map(map);

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

            for (int dir : a.dirs) {
                auto &&p = to_points(i, j, dir);

                auto [dest_row, dest_col] = p[1];

                bool flag = true;
                for (auto [a, b] : p) {
                    if (!map[a][b].empty) {
                        printf("at row %d col %d: tried move dir %d, blocked "
                               "by row %d col %d\n",
                            i, j, dir, a, b);
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    continue;

                // confirmed can move, propose move

                vector<int> temp;
                for (int d : a.dirs) {
                    if (d != dir)
                        temp.push_back(d);
                }
                temp.push_back(dir);

                a.dirs = temp;

                auto [d, e] = proposed[dest_row][dest_col];
                if (d != -1) {
                    proposed[dest_row][dest_col] = { -2, -2 };
                    printf(
                    "%d %d wants to move to %d %d but got blocked\n", i, j, dest_row, dest_col);
                    break;
                }

                proposed[dest_row][dest_col] = { i, j };
                printf(
                    "%d %d wants to move to %d %d\n", i, j, dest_row, dest_col);

                break;
            }
        }
    }

    cout << "\n";

    for (int i = 0; i < ROWS; ++i) {
        const vector<tuple<int, int>> &row = proposed[i];
        for (int j = 0; j < COLS; ++j) {
            auto [a, b] = row[j];
            if (a < 0)
                continue;

            cout << i << " " << j << "\n";

            // move tile
            out[i][j] = map[a][b];
            Tile &t = out[i][j];

            out[a][b] = Tile();
        }
    }
    return out;
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
    int ROWS = map.size();
    int COLS = map[0].size();

    for (int i = 0; i < 5; ++i) {
        map = advance_map(map, i);
    }

    int sum = 0;
    for (int i = 0; i < ROWS; ++i) {
        deque<Tile> &row = map[i];
        for (int j = 0; j < COLS; ++j) {
            sum += !row[j].empty;
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
    // solve("input");
}