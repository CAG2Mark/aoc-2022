#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    string left_str;
    string right_str;
    long long value;
    char op = 0;

    long long eval() {
        if (op) {
            long long l = left->eval();
            long long r = right->eval();

            switch (op) {
            case '+':
                return l + r;
            case '-':
                return l - r;
            case '*':
                return l * r;
            case '/':
                return l / r;
            default:
                return 0;
            }
        }
        return value;
    }
};

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    unordered_map<string, Node *> nodes;
    for (string ln : lns) {
        auto split = split_str(ln, ": ");
        string id = split[0];

        if ('0' <= split[1][0] && split[1][0] <= '9') {
            nodes[id] =
                new Node { nullptr, nullptr, "", "", stoi(split[1]), 0 };
        } else {
            char op = split[1][5];

            string spl = " ";
            auto spl2 = split_str(split[1], spl);
            string l = spl2[0];
            string r = spl2[2];

            nodes[id] = new Node { nullptr, nullptr, l, r, 0, op };
        }
    }

    for (auto n : nodes) {
        Node *node = get<1>(n);
        if (node->op) {
            node->left = nodes[node->left_str];
            node->right = nodes[node->right_str];
        }
    }

    cout << nodes["root"]->eval() << "\n";

    for (auto n : nodes) {
        delete get<1>(n);
    }
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