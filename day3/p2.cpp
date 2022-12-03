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
    for (int i = 0; i < lns.size(); i += 3) {
        bool r1[52] = {0}, r2[52] = {0}, r3[52] = {0};
        bool *r[] = {r1, r2, r3};
        for (int j = i; j < i + 3; ++j) {
            string ln = lns[j];
            for (char ch : ln) {
                int c = toPrior(ch);
                r[j-i][c] = 1;
            }
        }
        for (int j = 0; j < 52; ++j) {
            if (r1[j] && r2[j] && r3[j]) {
                sum += j + 1;
                break;
            }
        }
    }
    cout << sum << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    solve();
}