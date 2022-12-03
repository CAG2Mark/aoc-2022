#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

int toPrior(int a) {
    bool upper = !(a & 32);
    a = (a | 32) - 97;
    if (upper) a += 26;
    return a;
}

void solve() {
    vector<string> lns = get_lines();
    int sum = 0;
    for (string ln : lns) {
        int len = ln.length() / 2;
        int items[52] = {0};
        for (int i = 0; i < len; ++i) {
            int c = toPrior(ln[i]);
            items[c] = 1;
        }
        for (int i = len; i < 2*len; ++i) {
            char c = toPrior(ln[i]);
            if (!items[c]) continue;
            sum += c + 1;
            break;
        }
    }
    cout << sum << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}