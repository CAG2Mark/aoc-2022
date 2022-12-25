#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

const int MAP_WIDTH = 7;

typedef vector<vector<bool>> block_dt;
typedef vector<array<int, MAP_WIDTH>> board_dt;

const block_dt blocks[5] = { { { 1, 1, 1, 1 } },
    { { 0, 1, 0 }, { 1, 1, 1 }, { 0, 1, 0 } },
    { { 0, 0, 1 }, { 0, 0, 1 }, { 1, 1, 1 } }, { { 1 }, { 1 }, { 1 }, { 1 } },
    { {
          1,
          1,
      },
        { 1, 1 } } };

const int BLOCK_HEIGHTS[5] = { 1, 3, 3, 4, 2 };

/*
####
^

.#.
###
.#.
^

..#
..#
###
^

#
#
#
#
^

##
##
^
*/

// 0 = OK
// 1 = cannot shift left/right
// 2 = hit ground
bool can_move(board_dt &board, int x, int y, int block_type, bool wind) {
    const block_dt &b = blocks[block_type];
    int h = BLOCK_HEIGHTS[block_type];
    int w = b[0].size();

    int new_x = x + (wind ? 1 : -1);
    if (new_x < 0 || new_x + w - 1 >= MAP_WIDTH)
        return false;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            bool board_val = board[y + h - i - 1][new_x + j];
            bool block_val = b[i][j];
            if (board_val && block_val)
                return false;
        }
    }
    return true;
}

bool can_fall(board_dt &board, int x, int y, int block_type) {
    if (y == 0)
        return false;

    const block_dt &b = blocks[block_type];
    int h = BLOCK_HEIGHTS[block_type];
    int w = b[0].size();

    int new_y = y - 1;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            // cout << new_y + h - i - 1 << " " <<x+j << " " << board.size() <<
            // "\n";
            bool board_val = board[new_y + h - i - 1][x + j];
            bool block_val = b[i][j];

            // cout << x + j << " " << new_y + h - i - 1 << " " << board_val <<
            // "\n";
            if (board_val && block_val)
                return false;
        }
    }
    return true;
}

void write_block(board_dt &board, int x, int y, int block_type) {
    const block_dt &b = blocks[block_type];
    int h = BLOCK_HEIGHTS[block_type];
    int w = b[0].size();

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int &pos = board[y + h - i - 1][x + j];
            pos = pos || b[i][j];
        }
    }
}

void print(board_dt &board, int x, int y, int block_type, int top = -1) {
    const block_dt &b = blocks[block_type];
    int h = BLOCK_HEIGHTS[block_type];
    int w = b[0].size();

    if (x != -1) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int &pos = board[y + h - i - 1][x + j];
                if (b[i][j])
                    pos = 2;
            }
        }
    }

    int ll = 0;
    if (top != -1)
        ll = board.size() - 1 - top;
    for (int i = board.size() - 1; i >= ll; --i) {
        for (int b : board[i]) {
            if (b == 2)
                cout << "@";
            else
                cout << (b ? '#' : '.');
        }
        cout << "\n";
    }

    if (x != -1) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int &pos = board[y + h - i - 1][x + j];
                if (b[i][j])
                    pos = 0;
            }
        }
    }
    cout << "\n";
}

int rowHash(const array<int, MAP_WIDTH> &row) {
    int sum = 0;
    int pow = 1;
    for (int i : row) {
        sum += pow * (i != 0);
        pow <<= 1;
    }
    return sum;
}

const int CHECK_LEN = 1000;
const int KEEP_LEN = 1000;
typedef array<int, CHECK_LEN> repeat_t;

void solve(string filename) {
    long long int NUM_BLOCKS = 1000000000000;

    vector<string> lns = get_lines(filename);

    // true = right
    vector<bool> wind;
    lns[0] = strip_str(lns[0]);
    for (char c : lns[0]) {
        wind.push_back(c == '>');
    }

    // cout << wind << "\n";

    int highest = 0;
    board_dt board(7, { 0 });

    bool spawn_block = true;
    int block = 0;
    int w_pos = 0;

    int x, y;

    deque<repeat_t> signatures;
    deque<int> highests;

    bool skip = false;

    long long delta = 0;

    for (long long i = 0; i < NUM_BLOCKS; ++i) {
        // cout << i << " " << NUM_BLOCKS << "\n";

        if (!skip && highest > CHECK_LEN && i % 5 == 0) {
            repeat_t sig_new;
            for (int j = 0; j < CHECK_LEN; ++j) {
                sig_new[j] = rowHash(board[highest - j - 1]);
            }
            // cout << sig_new << "\n";

            int len = -1;
            for (int j = 0; j < signatures.size(); ++j) {
                if (sig_new != signatures[j])
                    continue;

                len = signatures.size() - j;

                // print(board, -1, -1, 0, 50);
            }
            if (len != -1) {
                int d = len * 5;
                long long rem = (NUM_BLOCKS - i) / d;
                i += d * rem;
                long long diff = highest - highests[highests.size() - len];
                delta = diff * rem;
                skip = true;
            }

            if (signatures.size() >= KEEP_LEN) {
                signatures.pop_front();
                highests.pop_front();
            }

            signatures.push_back(sig_new);
            highests.push_back(highest);
        }

        x = 2;
        y = board.size() - 4;
        spawn_block = false;
        // print(board, x, y, block);

        while (true) {

            bool w = wind[w_pos];
            w_pos = (w_pos + 1) % wind.size();

            bool status = can_move(board, x, y, block, w);
            if (status) {
                x += w ? 1 : -1;
            }
            if (can_fall(board, x, y, block)) {
                --y;
                continue;
            }
            break;
        }

        // Place block
        write_block(board, x, y, block);
        highest = max(highest, y + BLOCK_HEIGHTS[block]);
        spawn_block = true;
        block = (block + 1) % 5;

        // print(board, -1, -1, block);

        // maintain board
        if (board.size() < highest + 7) {
            board.resize(highest + 7, { 0 });
        }
    }

    cout << highest + delta << "\n";
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