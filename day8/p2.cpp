#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

int check_cell(int x, int y, int rows, int cols, const vector<vector<int>> &data) {
    int val = data[y][x];
    
    int a = 1;
    int i;
    for (i = x + 1; i < cols; ++i, ++a) {
        if (data[y][i] < val) continue;
        break;
    }
    if (i == cols) --a;

    int b = 1;
    for (i = x - 1; i >= 0; --i, ++b) {
        if (data[y][i] < val) continue;
        break;
    }
    if (i == -1) --b;

    int c = 1;
    for (i = y+1; i < rows; ++i, ++c) {
        if (data[i][x] < val) continue;
        break;
    }
    if (i == rows) --c;

    int d = 1;
    for (i = y - 1; i >= 0; --i, ++d) {
        if (data[i][x] < val) continue;
        break;
    }
    if (i == -1) --d;

    return a*b*c*d;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);
    vector<vector<int>> data;
    for (int i = 0; i < lns.size(); ++i) {
        string &ln = lns[i];
        data.push_back(vector<int>());
        for (char ch : ln) {
            data[i].push_back(ch - '0');
        }
    }

    int rows = data.size();
    int cols = data[0].size();

    int max_s = 0;
    
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            max_s = max(max_s, check_cell(i, j, rows, cols, data));
        }
    }

    cout << max_s << "\n";
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