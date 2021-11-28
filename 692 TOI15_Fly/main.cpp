#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;
using Pair = pair<int, int>;
const int N = 2020;
tuple<int, int, int, int> state[N][2 * N];
queue<Pair> q;
vector<vector<Pair>> bound;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a, c;
        char b, d;
        cin >> a >> b >> c >> d;
        state[i][0] = { a, c, b == 'R' ? 1 : -1, d == 'R' ? 1 : -1 };
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < 2 * m; j++) {
            auto [l, r, dl, dr] = state[i][j - 1];
            if (l == 0 || l == m) dl = -dl;
            if (r == 0 || r == m) dr = -dr;
            state[i][j] = { l + dl, r + dr, dl, dr };
        }
        for (int j = 0; j < 2 * m; j++) {
            auto [a, b, c, d] = state[i][j];
            auto [l, r] = minmax(a, b);
            state[i][j] = { l + 1, r - 1, c, d };
        }
    }
    for (int j = 0; j < 2 * m; j++) {
        state[0][j] = { 0, m, 0, 0 };
        state[n + 1][j] = { 0, m, 0, 0 };
    }
    bound.assign(n + 2, vector(2 * m, Pair(m, 0)));
    bound[0][0] = { 0, m };
    q.emplace(0, 0);
    while (not q.empty()) {
        auto [i, j] = q.front(); q.pop();
        if (i == n + 1) {
            cout << j;
            return 0;
        }
        auto [bl, br] = bound[i][j % (2 * m)];
        for (int d : {0, 1}) {
            int ni = i + d;
            int nj = (j + 1) % (2 * m);
            auto [sl, sr, _, __] = state[ni][nj];
            int nl = max(bl, sl);
            int nr = min(br, sr);
            auto [nbl, nbr] = bound[ni][nj];
            if (nl <= nr and (nl < nbl or nbr < nr)) {
                bound[ni][nj] = { min(nl, nbl), max(nbr, nr) };
                q.emplace(ni, j + 1);
            }
        }
    }
    return 1;
}