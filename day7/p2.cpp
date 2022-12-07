#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

vector<string> dirs_st;
map<string, unsigned long long> dirs;
map<string, int> lsed;

int total_sum = 0;

string dirname() {
    if (dirs_st.size() == 1) return "";
    return dirs_st.back();
}

void handle_line(string line) {
    if (line.empty())
        return;

    vector<string> spl = split_str(line, " ", true);
    if (line[0] == '$') {
        if (spl[1] == "cd") {
            if (spl[2] == "..") {
                dirs_st.pop_back();
            } else if (spl[2] == "/") {
                dirs_st.clear();
                dirs_st.push_back("/");
            } else {
                string dirn = dirname() + "/" + spl[2];
                dirs_st.push_back(dirn);
                if (dirs.find(dirn) == dirs.end()) {
                    dirs[dirn] = 0;
                    lsed[dirn] = 0;
                }
            }
            // cout << dirs_st << '\n';
        } else {
            ++lsed[dirs_st.back()];
        }

    } else {
        if (lsed[dirs_st.back()] >= 2)
            return;
        if (spl[0] == "dir")
            return;
        unsigned long long filesize = stoull(spl[0]);

        for (string dir : dirs_st) {
            dirs[dir] += filesize;
        }
        total_sum += filesize;
    }
}

void solve(string filename) {
    dirs.clear();
    dirs_st.clear();
    dirs["/"] = 0;
    lsed["/"] = 0;
    vector<string> lns = get_lines(filename);

    for (string ln : lns) {
        handle_line(ln);
    }

    unsigned long long sum = 0;
    unsigned long long min = dirs["/"];

    int free_space = 70000000 - dirs["/"];

    for (auto i : dirs) {
        if (free_space + i.second < 30000000) continue;
        if (i.second < min) min = i.second; 
    }

    cout << min << "\n";
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