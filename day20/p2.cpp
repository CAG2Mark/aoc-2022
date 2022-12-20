#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long val;
    Node *next;
    Node *prev;
};

void solve(string filename) {
    vector<string> lns = get_lines(filename);
    vector<Node *> nodes;

    for (string ln : lns) {
        if (string_is_whitespace(ln))
            continue;

        Node *n;
        if (nodes.empty()) {
            n = new Node { stoll(ln) * 811589153, nullptr, nullptr };
        } else {
            n = new Node { stoll(ln) * 811589153, nullptr, nodes.back() };
            nodes.back()->next = n;
        }

        nodes.push_back(n);
    }
    nodes.front()->prev = nodes.back();
    nodes.back()->next = nodes.front();

    int N = nodes.size();

    for (int i = 0; i < 10; ++i) {
        for (Node *n : nodes) {
            long long val = n->val;
            Node *cur = n;

            val = val % (N - 1);

            if (val == 0)
                continue;

            n->prev->next = n->next;
            n->next->prev = n->prev;

            if (val < 0) {
                val = -val;
                for (int i = 0; i < val + 1; ++i) {
                    cur = cur->prev;
                }
            } else {
                for (int i = 0; i < val; ++i) {
                    cur = cur->next;
                }
            }

            // link
            n->prev = cur;
            n->next = cur->next;
            n->prev->next = n;
            n->next->prev = n;
        }
    }

    Node *zero;
    for (Node *n : nodes) {
        if (n->val != 0)
            continue;
        zero = n;
        break;
    }
    long long sum = 0;
    for (int i = 0; i < 3001; ++i) {
        if (i == 1000 || i == 2000 || i == 3000) {
            cout << zero->val << '\n';
            sum += zero->val;
        }
        zero = zero->next;
    }

    cout << sum << "\n";

    for (Node *n : nodes)
        delete n;
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