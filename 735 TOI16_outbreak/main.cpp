#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;
using Pair = pair<int, int>;
// (x, y) => health, status, infect time
map<Pair, tuple<int, int, int>> mp;
using Tuple = tuple<int, int, int, int>;
//  time, -status, x, y 
priority_queue<Tuple, vector<Tuple>, greater<Tuple>> pq;

Pair d[] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int main() {
    int n, mxt, f, s, q;
    cin >> n >> mxt >> f >> s >> q;
    int inf = 0, qua = 0;
    for (int i = 0; i < n; i++) {
        int x, y, h, v;
        cin >> x >> y >> h >> v;
        mp[Pair(x, y)] = { h, 0, 0 };
        if (v) {
            if (h > q) {
                pq.emplace(0, -v, x, y);
            } else {
                auto& [h, z, t] = mp[Pair(x, y)];
                z = 3;
                qua += 1;
            }
        }
    }
    auto update = [&](int x, int y, int cur_t) {
        auto& [h, z, t] = mp[Pair(x, y)];
        if (z != 0) return;
        int sum = 0, cnt = 0;
        for (auto [dx, dy] : d) {
            int nx = x + dx;
            int ny = y + dy;
            if (mp.find(Pair(nx, ny)) == mp.end()) continue;
            auto [ch, cz, ct] = mp[Pair(nx, ny)];
            if (cz == 2) {
                cnt += 1;
                sum += ch + ct;
            }
        }
        if (cnt > 0) {
            t = max(cur_t, (h + sum + cnt - 1) / cnt - f);
            pq.emplace(t, -1, x, y);
        } else {
            t = 0;
        }
    };
    while (not pq.empty()) {
        auto [t, z, x, y] = pq.top(); pq.pop();
        if (t > mxt) {
            break;
        }
        auto& [h, cz, ct] = mp[Pair(x, y)];
        int nz = -z;
        if (nz <= cz || (nz == 1 && t != ct)) {
            continue;
        }
        cz = nz;
        if (nz == 1) { // got infected
            inf += 1;
            pq.emplace(t + max(1, h - s), -2, x, y); // should be t + 1 + max(0, h - s)
            pq.emplace(t + max(1, h - q), -3, x, y);
        } else { // update when spread or quarantine 
            if (nz == 3) {
                inf -= 1;
                qua += 1;
            }
            for (auto [dx, dy] : d) {
                int nx = x + dx;
                int ny = y + dy;
                if (mp.find(Pair(nx, ny)) == mp.end()) continue;
                update(nx, ny, t);
            }
        }
    }
    cout << inf << '\n' << qua;
}