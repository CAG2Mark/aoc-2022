#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int MINUTES = 30;

struct ValveTemp {
    string id;
    vector<string> neighbours;
    int flow;
};

struct State {
    string cur;
    int total_mins;

    vector<string> best_sequence;

    State(string cur, int total_mins) : cur(cur), total_mins(total_mins) { }
};

void floydWarshall(const unordered_map<string, ValveTemp> &valves,
    unordered_map<string, unordered_map<string, int>> &dists,
    unordered_map<string, unordered_map<string, string>> &nexts) {
    for (auto u : valves) {
        for (auto vi : get<1>(u).neighbours) {
            string ui = get<0>(u);

            dists[ui][vi] = 1;
            nexts[ui][vi] = vi;
        }
    }
    for (auto u : valves) {
        string ui = get<0>(u);
        dists[ui][ui] = 0;
        nexts[ui][ui] = ui;
    }
    for (auto u : valves) {
        for (auto v : valves) {
            for (auto w : valves) {
                string i = get<0>(u);
                string j = get<0>(v);
                string k = get<0>(w);

                if (dists[i][j] > dists[i][k] + dists[k][j]) {
                    dists[i][j] = dists[i][k] + dists[k][j];
                    nexts[i][j] = nexts[i][k];
                }
            }
        }
    }
}

void solve(string filename) {
    unordered_map<string, ValveTemp> valves;

    // count how many nonzero
    vector<ValveTemp> non_zero_v;

    vector<string> lns = get_lines(filename);
    for (string ln : lns) {
        vector<string> spl = split_str(ln, ";");
        vector<string> spl1 = split_str(spl[0], " has flow rate=");

        string cur = spl1[0].substr(6);
        int flow = stoi(spl1[1]);

        vector<string> tunnels = split_str(spl[1], ", ");
        tunnels[0] = tunnels[0].substr(tunnels[0].size() - 2, 2);
        valves[cur] = { cur, tunnels, flow };

        if (flow != 0) {
            non_zero_v.push_back(valves[cur]);
        }
    }

    unordered_map<string, unordered_map<string, int>> dists;
    unordered_map<string, unordered_map<string, string>> nexts;
    for (auto u : valves) {
        for (auto v : valves) {
            string ui = get<0>(u);
            string vi = get<0>(v);
            dists[ui][vi] = 100000;
            nexts[ui][vi] = "";
        }
    }

    floydWarshall(valves, dists, nexts);

    vector<unordered_map<string, State>> states(MINUTES);

    for (auto v : non_zero_v) {
        states[0][v.id] = { v.id, 0 };
    }

    for (int i = 0; i < MINUTES; ++i) {
        const unordered_map<string, State> &cur_states = states[i];
        for (auto s_ : cur_states) {
            State &s = get<1>(s_);
            for (auto v : non_zero_v) {
                if (v.id == s.cur) continue;

            }
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
    // solve("input");
}