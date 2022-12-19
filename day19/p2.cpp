#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <regex>

using namespace std;

struct Blueprint {
    int ore;
    int clay;
    int obsidian[2];
    int geode[2];

    void print() {
        cout << "ore bot: " << ore << "\tclay bot: " << clay
             << "\tobsidian bot: " << obsidian[0] << " ore, " << obsidian[1]
             << " clay\tgeode bot: " << geode[0] << " ore, " << geode[1]
             << " obsidian\n";
    }

    int max_ore = -1;

    int get_max_ore() {
        if (max_ore != -1)
            return max_ore;
        max_ore = max(ore, max(clay, max(obsidian[0], geode[0])));
        return max_ore;
    }
};

struct State {
    int ore = 0, ore_bot = 1, clay = 0, clay_bot = 0, obsidian = 0,
        obsidian_bot = 0, geode = 0, geode_bot = 0;

    unsigned long long get_hash() const {
        return ore + ore_bot * 100 + clay * 10000 + clay_bot * 1000000
            + obsidian * 100000000 + obsidian_bot * 10000000000
            + geode * 1000000000000 + geode_bot * 100000000000000;
    }

    bool worse_than(const State &other) const {
        return ore <= other.ore && ore_bot <= other.ore_bot
            && clay <= other.clay && clay_bot <= other.clay_bot
            && obsidian <= other.obsidian && obsidian_bot <= other.obsidian_bot
            && geode <= other.geode && geode_bot <= other.geode_bot;
    }

    void print() const {
        printf(
            "Ore: %d / %d, Clay: %d / %d, Obsidian: %d / %d, Geode: %d / %d\n",
            ore, ore_bot, clay, clay_bot, obsidian, obsidian_bot, geode,
            geode_bot);
    }
};

bool operator<(const State &s1, const State &s2) {
    return s1.get_hash() < s2.get_hash();
}

int recursion = 0;

int max_geodes(Blueprint &b) {
    set<State> states;
    states.insert(State());

    const int MINS = 32;

    for (int i = 0; i < MINS; ++i) {
        set<State> temp;

        for (const State &r : states) {
            State state = r;

            int ore_cap = b.get_max_ore() * (MINS - i);
            int clay_cap = b.obsidian[1] * (MINS - i);
            int obsidian_cap = b.geode[1] * (MINS - i);

            state.ore += state.ore_bot;
            state.clay += state.clay_bot;
            state.obsidian += state.obsidian_bot;
            state.geode += state.geode_bot;

            state.ore = min(state.ore, ore_cap);
            state.clay = min(state.clay, clay_cap);
            state.obsidian = min(state.obsidian, obsidian_cap);

            vector<State> candidates;

            {
                State s = state;
                candidates.push_back(s);
            }

            // build ore bot, but only if needed
            if (b.ore <= r.ore && state.ore_bot < b.get_max_ore()) {
                State s = state;
                s.ore -= b.ore;
                s.ore_bot += 1;

                candidates.push_back(s);
            }

            // build clay bot
            if (b.clay <= r.ore && state.clay_bot < b.obsidian[1]) {
                State s = state;
                s.ore -= b.clay;
                s.clay_bot += 1;

                candidates.push_back(s);
            }

            // build obsidian bot
            if (b.obsidian[0] <= r.ore && b.obsidian[1] <= r.clay
                && state.obsidian_bot < b.geode[1]) {
                State s = state;
                s.ore -= b.obsidian[0];
                s.clay -= b.obsidian[1];
                s.obsidian_bot += 1;

                candidates.push_back(s);
            }

            // build geode bot
            if (b.geode[0] <= r.ore && b.geode[1] <= r.obsidian) {
                State s = state;
                s.ore -= b.geode[0];
                s.obsidian -= b.geode[1];
                s.geode_bot += 1;

                candidates.push_back(s);
            }

            for (const State &r : candidates) {
                bool flag = true;
                for (auto i = temp.begin(); i != temp.end(); ) {
                    const State &p = *i;
                    if (p.worse_than(r)) {
                        temp.erase(i++);
                        continue;
                    }
                    if (r.worse_than(p)) {
                        flag = false;
                        break;
                    }
                    i++;
                }
                if (flag)
                    temp.insert(r);
            }
        }
        states = move(temp);
    }

    int max = 0;
    for (const State &r : states) {
        if (r.geode > max)
            max = r.geode;
    }
    return max;
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    int cnt = 0;
    vector<Blueprint> blueprints;

    int prod = 1;

    for (string ln : lns) {
        vector<int> a;

        ln = ln.substr(14);

        for (int i = 0; i < ln.size(); ++i) {
            char c = ln[i];
            if (c < '0' || c > '9')
                continue;
            a.push_back(stoi(strip_str(ln.substr(i, 2))));
            ++i;
        }

        Blueprint b = { a[0], a[1], { a[2], a[3] }, { a[4], a[5] } };
        
        prod *= max_geodes(b);

        if (++cnt == 3) break;
    }
    cout << prod << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    if (ifstream("input.test")) {
        cout << "TEST INPUT OUTPUT\n---------------------\n";
        // solve("input.test");
        cout << "\n";
    }
    cout << "OUTPUT\n---------------------\n";
    solve("input");
}