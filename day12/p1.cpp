#include "../utils/aocutils.h"
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

typedef tuple<int, int> point_dt;

int hash_point(int x, int y) { return y * 1000 + x; }

struct point_greater {
    bool operator()(const tuple<int, int> &a, const tuple<int, int> &b) {
        return get<1>(a) > get<1>(b);
    };
};

point_dt get_point(int hash) { 
    return { hash % 1000, hash / 1000 }; 
}

void solve(string filename) {
    vector<string> lns = get_lines(filename);

    int cur_x, cur_y, dest_x, dest_y;

    int height = lns.size();
    int width = lns[0].size();

    for (int y = 0; y < lns.size(); ++y) {
        string &ln = lns[y];
        for (int x = 0; x < ln.size(); ++x) {
            char ch = ln[x];
            if (ch == 'S') {
                cur_x = x;
                cur_y = y;
                ln[x] = 'a';
            } else if (ch == 'E') {
                dest_x = x;
                dest_y = y;
                ln[x] = 'z';
            }
        }
    }

    int dest_h = hash_point(dest_x, dest_y);
    int start_h = hash_point(cur_x, cur_y);

    unordered_map<int, int> dist;
    unordered_map<int, int> prev;
    vector<tuple<int, int>> data;
    priority_queue<tuple<int, int>, vector<tuple<int, int>>, point_greater>
        queue(data.begin(), data.end());

    dist[hash_point(cur_x, cur_y)] = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (hash_point(x, y) != hash_point(cur_x, cur_y)) {
                dist[hash_point(x, y)] = 1000000;
                prev[hash_point(x, y)] = -1;
            }

            tuple<int, int> point = { hash_point(x, y),
                dist[hash_point(x, y)] };

            queue.push(point);
        }
    }

    while (!queue.empty()) {
        tuple<int, int> cur = queue.top();
        queue.pop();
        point_dt p = get_point(get<0>(cur));
        int cur_x = get<0>(p), cur_y = get<1>(p);
        // get neighbours

        int cur_val = lns[cur_y][cur_x];
        
        vector<int> neighbours;
        if (cur_x - 1 >= 0 && lns[cur_y][cur_x - 1] - cur_val <= 1) {
            neighbours.push_back(hash_point(cur_x - 1, cur_y));
        }
        if (cur_x + 1 < width && lns[cur_y][cur_x + 1] - cur_val <= 1) {
            neighbours.push_back(hash_point(cur_x + 1, cur_y));
        }
        if (cur_y - 1 >= 0 && lns[cur_y - 1][cur_x] - cur_val <= 1) {
            neighbours.push_back(hash_point(cur_x, cur_y - 1));
        }
        if (cur_y + 1 < height && lns[cur_y + 1][cur_x] - cur_val <= 1) {
            neighbours.push_back(hash_point(cur_x, cur_y + 1));
        }

        for (int n : neighbours) {
            int alt = dist[get<0>(cur)] + 1;
            if (alt < dist[n]) {
                dist[n] = alt;
                prev[n] = get<0>(cur);
                queue.push({n, alt});
            }
        }
    }

    int steps = 0;
    int cur_point = dest_h;
    while (cur_point != start_h) {
        cout << get_point(cur_point) << "\n";
        cur_point = prev[cur_point];
        ++steps;
    }
    cout << steps << '\n';
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