#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    vector<vector<int>> map;

    int max_size = 0;
    int y;
    for (y = 0; y < lns.size(); ++y) {

        string ln = lns[y];
        if (string_is_whitespace(ln))
            break;

        max_size = max(max_size, (int)ln.size());
        if (!map.empty() && max_size > map[0].size()) {
            for (vector<int> &v : map)
                v.resize(max_size, 0);
        }
        map.push_back(vector<int>(max_size, 0));
        for (int x = 0; x < ln.size(); ++x) {
            char c = ln[x];
            switch (c) {
            case ' ':
                map[y][x] = 0;
                break;
            case '.':
                map[y][x] = 1;
                break;
            case '#':
                map[y][x] = 2;
                break;
            }
        }
    }

    ++y;
    string instr = lns[y];

    vector<string> list;

    for (int i = 0; i < instr.size(); ++i) {
        int cur = i;
        while ('0' <= instr[i] && instr[i] <= '9') {
            ++i;
        }
        if (cur == i)
            ++i;
        string ins = instr.substr(cur, i - cur);
        list.push_back(ins);
        --i;
    }

    int dir = 0;

    int cur_x, cur_y = 0;
    for (int i = 0; i < map[0].size(); ++i) {
        if (map[0][i] != 1)
            continue;
        cur_x = i;

        break;
    }

    for (string ins : list) {
        if ('0' > ins[0] || ins[0] > '9') {
            switch (ins[0]) {
            case 'L':
                dir = (dir + 3) % 4;
                break;
            case 'R':
                dir = (dir + 1) % 4;
                break;
            }
            continue;
        }

        int SIZE = map.size() / 4;

        const int RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3;

        int mv = stoi(ins);
        for (int i = 0; i < mv; ++i) {
            int new_x = cur_x, new_y = cur_y, new_dir = dir;
            switch (dir) {
            case 3:
                --new_y;
                break;
            case 0:
                ++new_x;
                break;
            case 1:
                ++new_y;
                break;
            case 2:
                --new_x;
                break;
            }

            if (new_x < 0 || new_x >= map[0].size() || new_y < 0
                || new_y >= map.size() || map[new_y][new_x] == 0) {
                // wrap around
                int x_quad = cur_x / SIZE;
                int y_quad = cur_y / SIZE;

                int x_p = cur_x % SIZE;
                int y_p = cur_y % SIZE;

                /*
                .XX
                .X.
                XX.
                X..
                */

                if (dir == RIGHT) {
                    if (y_quad == 0) {
                        new_dir = LEFT;
                        new_x = SIZE * 2 - 1;
                        new_y = 2 * SIZE + (SIZE - 1 - y_p);
                    } else if (y_quad == 1) {
                        new_dir = UP;
                        new_y = SIZE - 1;
                        new_x = SIZE * 2 + y_p;
                    } else if (y_quad == 2) {
                        new_dir = LEFT;
                        new_x = SIZE * 3 - 1;
                        new_y = SIZE - 1 - y_p;
                    } else {
                        new_dir = UP;
                        new_y = SIZE * 3 - 1;
                        new_x = SIZE + y_p;
                    }
                } else if (dir == DOWN) {
                    if (x_quad == 0) {
                        new_dir = DOWN;
                        new_x = SIZE * 2 + x_p;
                        new_y = 0;
                    } else if (x_quad == 1) {
                        new_dir = LEFT;
                        new_x = SIZE - 1;
                        new_y = SIZE * 3 + x_p;
                    } else {
                        new_dir = LEFT;
                        new_x = SIZE * 2 - 1;
                        new_y = SIZE + x_p;
                    }
                } else if (dir == LEFT) {
                    if (y_quad == 0) {
                        new_dir = RIGHT;
                        new_x = 0;
                        new_y = SIZE * 2 + (SIZE - 1 - y_p);
                    } else if (y_quad == 1) {
                        new_dir = DOWN;
                        new_x = y_p;
                        new_y = SIZE * 2;
                    } else if (y_quad == 2) {
                        new_dir = RIGHT;
                        new_x = SIZE;
                        new_y = SIZE - 1 - y_p;
                    } else {
                        new_dir = DOWN;
                        new_x = SIZE + y_p;
                        new_y = 0;
                    }
                } else if (dir == UP) {
                    if (x_quad == 0) {
                        new_dir = RIGHT;
                        new_x = SIZE;
                        new_y = SIZE + x_p;
                    } else if (x_quad == 1) {
                        new_dir = RIGHT;
                        new_x = 0;
                        new_y = SIZE * 3 + x_p;
                    } else {
                        new_dir = UP;
                        new_x = x_p;
                        new_y = SIZE * 4 - 1;
                    }
                }
            }

            if (map[new_y][new_x] == 2)
                break;

            cur_x = new_x;
            cur_y = new_y;
            dir = new_dir;
        }
    }

    cout << 4 * (cur_x + 1) + 1000 * (cur_y + 1) + dir << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    cout << "NOTE: CUBE HARDCODED, MAY NOT WORK FOR YOUR INPUT!\n";

    if (true && ifstream("input.test")) {
        cout << "TEST INPUT OUTPUT\n---------------------\n";
        solve("input.test");
        cout << "\n";
    }
    cout << "OUTPUT\n---------------------\n";
    solve("input");
}