#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int MINUTES = 26;

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

    int NUM_VALVES = valves_list.size();

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
    VALVES *= VALVES;

    vector<Valve> valves(VALVES);
    for (auto &v : valves_list) {
        int id = id_map[v.id];
        vector<int> neighbours;
        for (string a : v.neighbours)
            neighbours.push_back(id_map[a]);
        valves[id] = { id, neighbours, v.flow };
    }

    // dp
    vector<vector<int>> states(VALVES, vector<int>(1 << NON_ZERO, -1));

    vector<int> STATE_PRESSURES(1 << NON_ZERO, -1);

    for (int i = 0; i < STATE_PRESSURES.size(); ++i) {
        STATE_PRESSURES[i] = getPressure(i, non_zero_v);
    }

    for (int i = 0; i < VALVES; ++i) {
        // generate_states(non_zero_v, valves, states[get<0>(v)]);
        vector<int> &vec = states[i];
        for (int i = 0; i < vec.size(); ++i) {
            vec[i] = STATE_PRESSURES[i];
        }
    }

    for (int i = 1; i < MINUTES; ++i) {
        cout << i << "\n";
        vector<vector<int>> buf(VALVES, vector<int>(1 << NON_ZERO, 0));

        for (int i = 0; i < VALVES; ++i) {
            int v1 = i % NUM_VALVES;
            int v2 = i / NUM_VALVES;
            const Valve &val1 = valves[v1];
            const Valve &val2 = valves[v2];

            for (int j = 0; j < 1 << NON_ZERO; ++j) {
                int max_val = STATE_PRESSURES[j];

                // both move
                for (int adj1 : val1.neighbours) {
                    for (int adj2 : val2.neighbours) {
                        max_val = max(states[adj2 * NUM_VALVES + adj1][j], max_val);
                    }
                }

                // person switch, elephant move
                int new_state = j;
                if (v1 < NON_ZERO) {
                    new_state |= (1 << v1);
                }
                for (int adj2 : val2.neighbours) {
                    max_val = max(states[adj2 * NUM_VALVES + v1][new_state], max_val);
                }

                // elephant switch, person move
                new_state = j;
                if (v2 < NON_ZERO) {
                    new_state |= (1 << v2);
                }
                for (int adj1 : val1.neighbours) {
                    max_val = max(states[v2 * NUM_VALVES + adj1][new_state], max_val);
                }

                // case: switch current on, if it is a non-zero one
                new_state = j;
                if (v1 < NON_ZERO) {
                    new_state |= (1 << v1);
                }
                if (v2 < NON_ZERO) {
                    new_state |= (1 << v2);
                }
                max_val = max(max_val, states[i][new_state]);

                int new_val = STATE_PRESSURES[j] + max_val;
                buf[i][j] = new_val;
            }
        }
        states = buf;
    }

    cout << states[id_map["AA"] * NUM_VALVES + id_map["AA"]][0] << "\n";
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