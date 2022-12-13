#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Packet {
    vector<Packet *> children;
    int val;
    bool is_val;

    ~Packet() {
        for (Packet *p : children) {
            if (p)
                delete p;
        }
        children.clear();
    }

    Packet *&operator[](int i) {
        return children[i];
    }

    friend ostream &operator<<(ostream &os, const Packet &p);
    friend ostream &operator<<(ostream &os, const Packet *p);
};

ostream &operator<<(ostream &os, const Packet &p) {
    if (p.is_val) os << p.val;
    else os << p.children;
    return os;
}

ostream &operator<<(ostream &os, const Packet *p) {
    if (p->is_val) os << p->val;
    else os << p->children;
    return os;
}

int checkPackets(Packet &a, Packet &b) {
    int A = a.children.size(), B = b.children.size();

    cout << "compare " << a << " with " << b << "\n";

    int N = min(A, B);
    
    for (int i = 0; i < N; ++i) {
        Packet &p = *a[i];
        Packet &q = *b[i];

        if (p.is_val && q.is_val) {
            int r = p.val;
            int s = q.val;
            if (r < s) return 1;
            if (r == s) continue;
            return -1;
        } else if (!p.is_val && !q.is_val) {
            int res = checkPackets(p, q);
            if (res == 0) continue;
            return res;
        } else {
            if (p.is_val) { // Q is not val
                Packet *w = new Packet;
                w->is_val = false;
                Packet *t = new Packet;
                t->is_val = true;
                t->val = p.val;
                w->children.push_back(t);
                int res = checkPackets(*w, q);
                delete w;
                if (res == 0) continue;
                return res;
            } else { // Q is val
                Packet *w = new Packet;
                w->is_val = false;
                Packet *t = new Packet;
                t->is_val = true;
                t->val = q.val;
                w->children.push_back(t);
                int res = checkPackets(p, *w);
                delete w;
                if (res == 0) continue;
                return res;
            }
        }
    }

    if (A < B) return 1;
    if (A > B) return -1;

    return 0;
}

Packet *parsePacket(string ln) {
    ln = ln.substr(1, ln.size() - 2);
    vector<string> spl;

    int st = 0;
    int last_start = 0;
    for (int i = 0; i < ln.size(); ++i) {
        char c = ln[i];
        if (c == '[')
            ++st;
        else if (c == ']')
            --st;
        else if (c == ',' && st == 0) {
            spl.push_back(ln.substr(last_start, i - last_start));
            last_start = i + 1;
        }
    }
    if (ln.size() != 0)
        spl.push_back(ln.substr(last_start, ln.size() - last_start));

    Packet *ret = new Packet;
    ret->is_val = false;

    for (string s : spl) {
        Packet *p;

        if (s[0] == '[') {
            p = parsePacket(s);
            p->is_val = false;
        } else {
            p = new Packet;
            p->is_val = true;
            p->val = stoi(s);
        }

        ret->children.push_back(p);
    }

    return ret;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);
    int i = 0;

    int sum = 0;

    Packet *a;
    Packet *b;

    while (i < lns.size()) {
        string ln = lns[i];

        if (i % 3 == 0) {
            a = parsePacket(ln);
        } else if (i % 3 == 1) {
            b = parsePacket(ln);
            // cout << 
            if (checkPackets(*a, *b) >= 1) {
                cout << i / 3 + 1 << "\n";
                sum += i / 3 + 1;
            }
        } else {
            delete a;
            delete b;
        }

        ++i;
    }

    cout << sum << "\n";

    delete a;
    delete b;
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