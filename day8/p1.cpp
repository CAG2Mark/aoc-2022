#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

bool check_cell(int x, int y, int rows, int cols, const vector<vector<int>> &data) {
    int val = data[y][x];
    
    bool flag = true;
    for (int i = x + 1; i < cols; ++i) {
        if (data[y][i] < val) continue;
        flag = false;
        break;
    }
    if (flag) return true;

    flag = true;
    for (int i = x - 1; i >= 0; --i) {
        if (data[y][i] < val) continue;
        flag = false;
        break;
    }
    if (flag) return true;

    flag = true;
    for (int i = y+1; i < rows; ++i) {
        if (data[i][x] < val) continue;
        flag = false;
        break;
    }
    if (flag) return true;

    flag = true;
    for (int i = y - 1; i >= 0; --i) {
        if (data[i][x] < val) continue;
        flag = false;
        break;
    }
    if (flag) return true;

    return false;
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

    int sum = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += check_cell(i, j, rows, cols, data);
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
    solve("input");
}