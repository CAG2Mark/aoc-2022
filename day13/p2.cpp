#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Packet {
    vector<Packet *> children;
    int val;
    bool is_val;

    bool is_divider = false;

    ~Packet() {
        for (Packet *p : children) {
            if (p)
                delete p;
        }
        children.clear();
    }

    Packet *operator[](int i) const {
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

int checkPackets(const Packet &a, const Packet &b) {
    int A = a.children.size(), B = b.children.size();

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

struct PacketComp {
    inline bool operator()(Packet *a, Packet *b) {
        return checkPackets(*a, *b) == 1;
    }
};


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

    vector<Packet *> list;
    for (string ln : lns) {
        if (string_is_whitespace(ln)) continue;

        list.push_back(parsePacket(ln));
    }

    Packet *a = parsePacket("[[2]]");
    a->is_divider = true;
    Packet *b = parsePacket("[[6]]");
    b->is_divider = true;

    list.push_back(a);
    list.push_back(b);

    sort(list.begin(), list.end(), PacketComp());

    int prod = 1;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i]->is_divider) {
            prod *= (i+1);
        }
    }

    cout << prod << "\n";

    for (Packet *p : list) delete p;
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