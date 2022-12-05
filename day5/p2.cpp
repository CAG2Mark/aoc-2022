#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

void solve() {
    vector<string> lns = get_lines();

    vector<deque<char>> stacks(9);

    int i = 0;
    for (; i < lns.size(); ++i) {
        string ln = lns[i];
        if (string_is_whitespace(ln)) break;

        if (ln[1] == '1') break;

        for (int i = 0; i < 9; ++i) {
            int pos = 1 + 4*i;
            if (ln[pos] == ' ') continue;
            stacks[i].push_front(ln[pos]);
        }
    }

    i += 2;
    for (; i < lns.size(); ++i) {
        vector<string> spl = split_str(lns[i], " ");

        int amount = stoi(spl[1]);
        int from = stoi(spl[3]) - 1;
        int to = stoi(spl[5]) - 1;

        vector<char> a;
        for (int i = 0; i < amount; ++i) {
            char mv = stacks[from].back();
            a.push_back(mv);
            stacks[from].pop_back();
        }
        for (char c : a) {
            stacks[to].push_back(a.back());
            a.pop_back();
        }
    }

    for (int i = 0; i < 9; ++i) {
        cout << stacks[i].back();
    }
    cout << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}