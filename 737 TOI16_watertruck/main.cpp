#include <iostream>
#include <vector>
#include <map>
#include <queue>

#define em emplace
#define eb emplace_back

using namespace std;
using Pair = pair<int, int>;
using Tuple = tuple<int, int, int>;

const int N = 1e5 + 10;
const int INF = 1e9 + 10;

vector<Pair> g[N];
int deg[N];

vector<Tuple> smg[N];
map<vector<int>, int> path_no;

int main() {
    int n, m, ans = 0;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].eb(v, w);
        g[v].eb(u, w);
        deg[u] += 1;
        deg[v] += 1;
    }

    queue<int> q;
    for (int u = 1; u < n; u++) {
        if (deg[u] == 1) {
            q.push(u);
        }
    }
    bool visited[N]{};
    while (not q.empty()) {
        int u = q.front(); q.pop();
        visited[u] = true;
        for (auto [v, w] : g[u]) if (not visited[v]) {
            ans += w * 2;
            deg[v] -= 1;
            if (deg[v] == 1 && v) {
                q.em(v);
            }
        }
    }
    bool corner[N] = { true };
    int label[N]{};
    int l = 1;
    for (int u = 1; u < n; u++) {
        if (deg[u] > 2 and not visited[u]) {
            corner[u] = true;
            label[u] = l++;
        }
    }
    int e = 0;
    for (int u = 0; u < n; u++) if (corner[u]) {
        int sum_loop = 0;
        for (auto [v, w] : g[u]) if (not visited[v]) {
            int sum = w;
            int cur = v;
            int prv = u;
            vector<int> path{ u, v };
            while (not corner[cur]) {
                for (auto x : g[cur]) {
                    tie(v, w) = x;
                    if (v != prv and not visited[v]) break;
                }
                path.eb(v);
                prv = cur;
                sum += w;
                cur = v;
            }
            if (cur == u) {
                sum_loop += sum;
                continue;
            }
            int x = label[u];
            int y = label[cur];
            if (x > y) {
                reverse(path.begin(), path.end());
            }
            if (path_no.find(path) == path_no.end()) {
                path_no[path] = e++;
            }
            smg[x].eb(y, sum, path_no[path]);
        }
        ans += sum_loop / 2;
    }
    vector<vector<int>> dist(l, vector<int>(1 << e, INF));
    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> pq;
    pq.em(dist[0][0] = 0, 0, 0);
    while (not pq.empty()) {
        auto [d, u, b] = pq.top(); pq.pop();
        for (auto [v, w, pn] : smg[u]) {
            int nw = dist[u][b] + w;
            int nb = b | (1 << pn);
            if (dist[v][nb] > nw) {
                dist[v][nb] = nw;
                pq.em(dist[v][nb], v, nb);
            }
        }
    }
    cout << ans + dist[0][(1 << e) - 1];
    return 0;
}