/*
 * Algorithm: Dijkstra with state, Convex
 * (There is an alternative solution which is simpler)
 */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <tuple>
#include <climits>
#define all(x) (x).begin(), (x).end()

using namespace std;
using lli = long long int;
using Graph = vector<vector<pair<int, int>>>;
const lli INF = 1e18;

auto dijk(Graph& g, int s, int t) {
    int n = g.size();
    vector<vector<lli>> dist(n, vector<lli>(n, INF));
    using Tuple = tuple<lli, int, int>;
    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> pq;
    pq.emplace(dist[s][0] = 0, 0, s);
    while (not pq.empty()) {
        auto [d, c, u] = pq.top(); pq.pop();
        if (c == n) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v][c + 1] > d + w) {
                dist[v][c + 1] = d + w;
                pq.emplace(dist[v][c + 1], c + 1, v);
            }
        }
    }
    return dist[t];
}

vector<tuple<lli, int, lli>> q;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, t, m, l;
    cin >> n >> s >> t >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    }
    cin >> l;
    auto dist = dijk(g, s, t);
    vector<pair<lli, int>> tmp, v;
    for (int i = 1; i < n; i++) {
        if (dist[i] != INF) {
            int nd = dist[i], nc = i - 1;
            tmp.emplace_back(nd, nc);
        }
    }
    sort(all(tmp));
    for (auto [nd, nc] : tmp) {
        if (not v.empty()) {
            auto [d, c] = v.back();
            if (nc > c) continue;
            while (v.size() > 1) {
                auto [d, c] = v.back();
                auto [pd, pc] = *(v.end() - 2);
                if ((nd - pd) * (pc - c) <= (d - pd) * (pc - nc)) {
                    v.pop_back();
                } else {
                    break;
                }
            }
        }
        v.emplace_back(nd, nc);
    }
    // for (auto [d, c] : v) {
    //     cout << d << ' ' << c << '\n';
    // }
    using Tuple = tuple<lli, int, lli>;
    for (int i = 0; i < l; i++) {
        int h;
        cin >> h;
        q.emplace_back(h, i, 0);
    }
    sort(all(q));
    m = v.size();
    auto find_next = [&v, m](int i) {
        auto [d, c] = v[i];
        for (int j = i; j < m; j++) {
            auto [nd, nc] = v[j];
            if (nc < c) {
                return j;
            }
        }
        return m;
    };
    for (int i = 0, j = 0, k = 0; k < l; k++) {
        auto& [h, _, ans] = q[k];
        while (j < m) {
            auto [d, c] = v[i];
            auto [nd, nc] = v[j];
            if (nd + nc * h > d + c * h) break;
            i = j;
            j = find_next(j);
        }
        auto [d, c] = v[i];
        ans = d + c * h;
    }
    sort(all(q), [](const Tuple& l, const Tuple& r) {
        const auto& [_, i, __] = l;
        const auto& [$, j, $$] = r;
        return i < j;
        });
    for (int i = 0; i < l; i++) {
        auto [_, __, ans] = q[i];
        cout << ans << ' ';
    }
}
