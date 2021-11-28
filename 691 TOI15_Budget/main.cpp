#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#define all(x) x.begin(), x.end()

using namespace std;
using Pair = pair<int, int>;
using Tuple = tuple<int, int, int>;
using Vector = vector<Pair>;
using Graph = vector<Vector>;

vector<int> par;
int find_par(int u) {
    return par[u] = par[u] == u ? u : find_par(par[u]);
}
bool merge(int u, int v) {
    u = find_par(u);
    v = find_par(v);
    if (u == v) {
        return false;
    }
    par[u] = par[v];
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, p;
    cin >> n >> m;
    vector<Tuple> edges;
    for (int i = 0; i < n; i++) {
        par.push_back(i);
    }
    int edge_cnt = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w, r;
        cin >> u >> v >> w >> r;
        if (r) {
            if (merge(u, v)) {
                edge_cnt += 1;
            }
        } else {
            edges.emplace_back(w, u, v);
        }
    }
    cin >> p;
    vector<Pair> pack;
    for (int i = 0; i < p; i++) {
        int s, c;
        cin >> s >> c;
        pack.emplace_back(s, c);
    }
    sort(all(pack), [](const Pair& l, const Pair& r) {
        return tie(l.first, r.second) < tie(r.first, l.second);
        });
    auto [_, min_price] = pack[p - 1];
    for (int i = p - 1; ~i; i--) {
        auto& [_, cur_price] = pack[i];
        cur_price = min_price = min(min_price, cur_price);
    }
    sort(all(edges));
    int ans = 0;
    for (int i = 0; edge_cnt < n - 1; i++) {
        auto [w, u, v] = edges[i];
        if (merge(u, v)) {
            auto [s, c] = *lower_bound(all(pack), Pair(w, 0));
            ans += c;
            edge_cnt += 1;
        }
    }
    cout << ans;
}