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

    // count whitespaces
    vector<int> row_emptycnt(map.size(), 0);
    for (int i = 0; i < map.size(); ++i) {
        row_emptycnt[i] = count(map[i].begin(), map[i].end(), 0);
    }
    vector<int> col_emptycnt(map[0].size(), 0);
    for (int j = 0; j < map[0].size(); ++j) {
        for (int i = 0; i < map.size(); ++i) {
            col_emptycnt[j] += map[i][j] == 0;
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

        int mv = stoi(ins);
        for (int i = 0; i < mv; ++i) {
            // cout << cur_x << " " << cur_y << "\n";
            int new_x = cur_x, new_y = cur_y;
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

            if (new_x < 0 || new_x >= map[0].size() || new_y < 0 || new_y >= map.size() || map[new_y][new_x] == 0) {
                // wrap around

                switch (dir) {
                case 3:
                    new_y =
                        (new_y - col_emptycnt[new_x] + map.size()) % map.size();
                    break;
                case 0:
                    new_x = (new_x + row_emptycnt[new_y] + map[0].size())
                        % map[0].size();
                    break;
                case 1:
                    new_y = (new_y + col_emptycnt[new_x] + map.size())
                        % map.size();
                    break;
                case 2:
                    new_x = (new_x - row_emptycnt[new_y] + map[0].size())
                        % map[0].size();
                    break;
                }

            }

            if (map[new_y][new_x] == 2)
                break;

            cur_x = new_x;
            cur_y = new_y;
        }
    }

    cout << 4 * (cur_x + 1) + 1000 * (cur_y + 1) + dir << "\n";
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