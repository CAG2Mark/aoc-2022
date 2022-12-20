#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

struct ValveTemp {
    string id;
    vector<string> neighbours;
    int flow;
};

struct Valve {
    int id;
    vector<int> neighbours;
    int flow;
};

int getPressure(int state, const vector<ValveTemp> &valves) {
    int sum = 0;
    for (int i = 0; i < valves.size(); ++i) {
        sum += valves[i].flow * !!(state & (1 << i));
    }
    return sum;
}

const int MINUTES = 30;
const int PLAYERS = 1;

void solve(string filename) {
    vector<ValveTemp> valves_list;

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
        valves_list.push_back({ cur, tunnels, flow });

        if (flow != 0) {
            non_zero_v.push_back(valves_list.back());
        }
    }

    int NON_ZERO = non_zero_v.size();

    // convert to IDs
    // optimisation: store non-zero at the front
    unordered_map<string, int> id_map;
    for (int i = 0; i < NON_ZERO; ++i) {
        id_map[non_zero_v[i].id] = i;
    }
    int i = NON_ZERO;
    for (auto &v : valves_list) {
        if (v.flow != 0)
            continue;
        id_map[v.id] = i++;
    }

    int VALVES = valves_list.size();

    vector<Valve> valves(VALVES);
    for (auto &v : valves_list) {
        int id = id_map[v.id];
        vector<int> neighbours;
        for (string a : v.neighbours)
            neighbours.push_back(id_map[a]);
        valves[id] = { id, neighbours, v.flow };
    }

    // dp
    vector<vector<int>> states(VALVES, vector<int>(1 << NON_ZERO, 0));

    for (int i = 1; i < MINUTES * PLAYERS; ++i) {
        vector<vector<int>> buf(VALVES, vector<int>(1 << NON_ZERO, 0));

        for (int j = 0; j < VALVES; ++j) {
            const Valve &val = valves[j];
            for (int k = 0; k < 1 << NON_ZERO; ++k) {
                if (i % MINUTES == 0) {
                    buf[j][k] = states[id_map["AA"]][k];
                    continue;
                }

                int max_val = 0;

                // case: move to adjacent
                for (int adj : val.neighbours) {
                    max_val = max(max_val, states[adj][k]);
                }

                // case: switch current on, if it is a non-zero one
                if (j < NON_ZERO) {
                    int new_state = k | (1 << j);
                    if (new_state > k) {
                        int add_press = valves[j].flow * (i % MINUTES);
                        max_val =
                            max(max_val, add_press + states[j][new_state]);
                    }
                }

                buf[j][k] = max_val;
            }
        }
        states = buf;
    }
    cout << states[id_map["AA"]][0] << "\n";

    // cout << getPressure(0, non_zero_v) << "\n";
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