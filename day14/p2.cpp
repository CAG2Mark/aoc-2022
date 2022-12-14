#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

tuple<int, int> sand_move(vector<vector<char>> &board, int x, int y) {
    int ret_x, ret_y;
    if (board[y + 1][x] == 0) {
        ret_x = x;
        ret_y = y + 1;
    } else if (board[y + 1][x - 1] == 0) {
        ret_x = x - 1;
        ret_y = y + 1;
    } else if (board[y + 1][x + 1] == 0) {
        ret_x = x + 1;
        ret_y = y + 1;
    } else {
        return { -1, 0 };
    }

    return { ret_x, ret_y };
}

void draw_line(vector<vector<char>> &board, int x1, int x2, int y1, int y2) {
    if (x1 != x2) {
        int l = min(x1, x2);
        int u = max(x1, x2);
        for (int j = l; j <= u; ++j) {
            board[y1][j] = 1;
        }
    } else {
        int l = min(y1, y2);
        int u = max(y1, y2);
        for (int j = l; j <= u; ++j) {
            board[j][x1] = 1;
        }
    }
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);
    vector<vector<char>> board(220, vector<char>(1200, 0));

    int max_y = 0;
    for (string ln : lns) {
        vector<string> coords = split_str(ln, " -> ");
        for (int i = 1; i < coords.size(); ++i) {
            vector<string> spl1 = split_str(coords[i - 1], ",");
            int x1 = stoi(spl1[0]);
            int y1 = stoi(spl1[1]);

            vector<string> spl2 = split_str(coords[i], ",");
            int x2 = stoi(spl2[0]);
            int y2 = stoi(spl2[1]);

            max_y = max(y1, max_y);
            max_y = max(y2, max_y);

            draw_line(board, x1, x2, y1, y2);
        }
    }

    // find min y coordinate

    draw_line(board, 0, 1199, max_y + 2, max_y + 2);

    int cntr = 0;
    while (true) {
        ++cntr;
        int cur_x = 500, cur_y = 0;
        int status = 0;
        while (true) {
            auto t = sand_move(board, cur_x, cur_y);

            int tx = get<0>(t);
            int ty = get<1>(t);
            if (tx == -1) {
                status = 1;
                break;
            }

            cur_x = get<0>(t);
            cur_y = get<1>(t);
        }


        if (status == 1) {
            board[cur_y][cur_x] = 2;
            if (cur_x == 500 && cur_y == 0) {
                break;
            }
            continue;
        }
    }

    cout << cntr << "\n";
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