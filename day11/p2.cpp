#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Monkey {
    int id;
    deque<unsigned long long> items;
    bool multiply;
    int opval;
    int divide;
    int true_monkey;
    int false_monkey;

    int cnt = 0;
};

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    int id;
    deque<unsigned long long> items;
    bool multiply;
    int opval;
    int divide;
    int true_m, false_m;

    int prod = 1;

    vector<Monkey *> monkies;

    for (string ln : lns) {
        ln = strip_str(ln);

        if (string_is_whitespace(ln)) {
            Monkey *m = new Monkey;
            m->id = id;
            m->items = items;
            m->multiply = multiply;
            m->opval = opval;
            m->divide = divide;
            m->true_monkey = true_m;
            m->false_monkey = false_m;
            items = deque<unsigned long long>();
            monkies.push_back(m);
            continue;
        }

        if (ln[0] == 'M') {
            id = ln[7] - '0';
        } else if (ln[0] == 'S') {
            vector<string> spl = split_str(split_str(ln, "items: ")[1], ", ");
            for (string a : spl)
                items.push_back(stoi(a));
        } else if (ln[0] == 'O') {
            string s = split_str(ln, "Operation: new = old ")[1];
            multiply = s[0] == '*';
            if (s.substr(2)[0] == 'o') {
                opval = -1;
            } else {
                opval = stoi(s.substr(2));
            }
        } else if (ln[0] == 'T') {
            string s = split_str(ln, " by ")[1];
            divide = stoi(s);
            prod *= divide;
        } else if (ln[3] == 't') {
            true_m = ln.back() - '0';
        } else if (ln[3] == 'f') {
            false_m = ln.back() - '0';
        }
    }

    Monkey *m =
        new Monkey { id, items, multiply, opval, divide, true_m, false_m };
    monkies.push_back(m);

    

    for (int i = 0; i < 10000; ++i) {
        if (i % 1000 == 0) {
            // cout << "ROUND " << i << "\n";
            for (Monkey *m : monkies) {
                // cout << m->cnt << "\n";
            }
            // cout << "\n";
        }

        for (Monkey *m : monkies) {
            while (!m->items.empty()) {
                // cout << m->items << "\n";
                ++m->cnt;
                unsigned long long it = m->items.front();
                m->items.pop_front();

                unsigned long long n;
                if (m->multiply && m->opval == -1)
                    n = it * it;
                else if (m->multiply)
                    n = it * m->opval;
                else
                    n = it + m->opval;

                n %= prod;

                // cout << it << " " << m->opval << " " << n << "\n";

                if (n % m->divide == 0) {
                    monkies[m->true_monkey]->items.push_back(n);
                } else {
                    monkies[m->false_monkey]->items.push_back(n);
                }
            }
            // cout << "\n";
        }
    }
    for (Monkey *m : monkies) {
        // cout << m->items << "\n";
    }
    // cout << "\n";

    vector<unsigned long long> cnts;
    for (Monkey *m : monkies) {
        cnts.push_back(m->cnt);
        delete m;
    }

    sort(cnts.begin(), cnts.end());
    // cout << cnts << "\n";
    cout << cnts[cnts.size() - 1] * cnts[cnts.size() - 2] << "\n";
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