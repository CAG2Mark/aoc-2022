#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    unordered_map<char, long long> vals = {
        { '0', 0 },
        { '1', 1 },
        { '2', 2 },
        { '-', -1 },
        { '=', -2 },
    };

    unordered_map<long long, char> chars = {
        { 0, '0' },
        { 1, '1' },
        { 2, '2' },
        { -1, '-' },
        { -2, '=' },
    };

    long long sum = 0;
    for (string ln : lns) {
        long long pow = 1;
        long long val = 0;
        for (int i = ln.size() - 1; i >= 0; --i) {
            char c = ln[i];
            val += vals[c] * pow;
            pow *= 5;
        }
        sum += val;
    }

    string num = "";
    while (sum) {
        bool carry = false;
        long long m = sum % 5;
        if (m > 2) {
            m = m - 5;
            carry = true;
        }
        num = chars[m] + num;
        sum /= 5;
        if (carry) {
            ++sum;
        }
    }
    cout << num << "\n";
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