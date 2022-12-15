#include "../utils/aocutils.h"
#include <bits/stdc++.h>

using namespace std;

struct Sensor {
    int x, y;
    int bx, by;
};

struct Range {
    int low, up;

    bool operator<(const Range &other) { return low < other.low; }
};

ostream &operator<<(ostream &os, const Range &r) {
    return os << "[" << r.low << ", " << r.up << ")";
}

ostream &operator<<(ostream &os, const Sensor &r) {
    return os << "(" << r.x << ", " << r.y << ")";
}

Range getRowExcl(const Sensor &s, int row) {
    int radius = abs(s.x - s.bx) + abs(s.y - s.by);

    int rWidth = max(-1, radius - abs(row - s.y));

    return { s.x - rWidth, s.x + rWidth + 1 };
}

vector<Range> getRange(const vector<Sensor> &sensors, int ROW) {
    vector<Range> ranges;

    for (const Sensor &s : sensors) {
        auto excl = getRowExcl(s, ROW);

        // cout << excl << "\n";

        if (excl.low > excl.up)
            continue;

        ranges.push_back(excl);
    }

    sort(ranges.begin(), ranges.end());
    // cout << "\n";
    vector<Range> st;

    st.push_back(ranges[0]);

    for (int i = 1; i < ranges.size(); ++i) {
        Range top = st.back();
        // current no overlap
        if (top.up < ranges[i].low) {
            st.push_back(ranges[i]);
            continue;
        }

        if (top.up < ranges[i].up) {
            top.up = ranges[i].up;
            st.pop_back();
            st.push_back(top);
        }
    }

    return st;
}

void solve(string filename, int ROW = 20) {

    vector<string> lns = get_lines(filename);

    vector<Sensor> sensors;

    for (string ln : lns) {
        auto spl1 = split_str(ln, ": closest beacon is at ");
        string a = spl1[0].substr(10);
        string b = spl1[1];

        auto snsr = split_str(a, ", ");
        int snsr_x = stoi(snsr[0].substr(2));
        int snsr_y = stoi(snsr[1].substr(2));

        auto beacon = split_str(b, ", ");
        int beacon_x = stoi(beacon[0].substr(2));
        int beacon_y = stoi(beacon[1].substr(2));

        sensors.push_back(Sensor { snsr_x, snsr_y, beacon_x, beacon_y });
    }

    int i = ROW;
    for (int i = ROW;; --i) {
        vector<Range> intervals = getRange(sensors, i);
        // cout << intervals << "\n";
        if (intervals.size() == 1) continue;
        for (auto r : intervals) {
            if (r.up > ROW) break;
            
            cout << r.up << " " << i << "\n";
            cout << (unsigned long long)(r.up) * 4000000 + i << "\n";
            return;
        }
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
    solve("input", 4000000);
}