#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    string left_str;
    string right_str;
    string id = "";
    long long value;
    char op = 0;

    long long eval(bool &success) {
        if (success == false)
            return 0;
        if (id == "humn") {
            success = false;
            return 0;
        }

        if (op) {
            long long l = left->eval(success);
            if (!success)
                return 0;
            long long r = right->eval(success);
            if (!success)
                return 0;

            switch (op) {
            case '+':
                return l + r;
            case '-':
                return l - r;
            case '*':
                return l * r;
            case '/':
                return l / r;
            case '=':
                return l == r;
            default:
                return 0;
            }
        }
        return value;
    }
};

// right: unknown is on right
long long inverse(char op, long long target, long long val, bool right) {
    if (op == '=')
        return val;
    if (op == '+')
        return target - val;
    if (op == '-') {
        if (right) {
            return val - target;
        }
        return target + val;
    }
    if (op == '*')
        return target / val;
    if (op == '/') {
        if (right) {
            return val / target;
        }
        return target * val;
    }
    cout << "ERROR!\n";
    return -1;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    unordered_map<string, Node *> nodes;
    for (string ln : lns) {
        auto split = split_str(ln, ": ");
        string id = split[0];

        if ('0' <= split[1][0] && split[1][0] <= '9') {
            nodes[id] =
                new Node { nullptr, nullptr, "", "", id, stoi(split[1]), 0 };
        } else {
            char op = split[1][5];

            string spl = " ";
            auto spl2 = split_str(split[1], spl);
            string l = spl2[0];
            string r = spl2[2];

            if (id == "root")
                op = '=';

            nodes[id] = new Node { nullptr, nullptr, l, r, id, 0, op };
        }
    }

    for (auto n : nodes) {
        Node *node = get<1>(n);
        if (node->op) {
            node->left = nodes[node->left_str];
            node->right = nodes[node->right_str];
        }
    }

    Node *node = nodes["root"];
    long long target = 1;
    while (node->id != "humn") {
        bool success = true;

        if (node->left == nullptr || node->right == nullptr)
            cout << "ERROR!\n";

        long long l = node->left->eval(success);
        success = true;
        long long r = node->right->eval(success);
        if (success) {
            target = inverse(node->op, target, r, false);
            node = node->left;
        } else {
            target = inverse(node->op, target, l, true);
            node = node->right;
        }
    }
    cout << target << "\n";

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