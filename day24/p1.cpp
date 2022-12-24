#include <bits/stdc++.h>
#include "../utils/aocutils.h"

using namespace std;

void solve(string filename) {
    vector<string> lns = get_lines(filename);
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