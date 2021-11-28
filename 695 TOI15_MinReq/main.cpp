#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
#define all(x) x.begin(), x.end()

using namespace std;
using Tuple = tuple<int, int, int>;
using Vector = vector<int>;
const int M = 1e7, N = 10;
int ps[M + 2], lift[N], a[N], t[N];

bool can_lift(int mxw, int mxt, int l, int r) {
    int t = 0;
    while (l < r) {
        if (++t > mxt) {
            return false;
        }
        int nl = upper_bound(ps + l, ps + r, mxw + ps[l - 1]) - ps;
        if (nl == l) {
            return false;
        }
        l = nl;
    }
    return true;
};


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m, x;
    cin >> n >> m >> x;
    for (int i = 0; i < n; i++) {
        cin >> lift[i];
    }
    sort(lift, lift + n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int j = 1; j <= m; j++) {
        cin >> ps[j];
        ps[j] += ps[j - 1];
    }
    for (int k = 0; k < x; k++) {
        cin >> t[k];
    }

    vector<int> group(n + 1, m);
    for (int k = 0; k < x; k++) {
        for (int i = 0; i < n; i++) {
            cin >> group[i];
        }
        auto can_simulate = [&]() {
            vector<bool> mkl(n, false);
            auto use_a_lift = [&](int l, int r) {
                for (int i = 0; i < n; i++) {
                    if (mkl[i]) continue;
                    if (can_lift(lift[i] - a[i], t[k], l, r)) {
                        mkl[i] = true;
                        return true;
                    }
                }
                return false;
            };
            for (int j = 0; j < n; j++) {
                if (not use_a_lift(group[j], group[j + 1])) {
                    return false;
                }
            }
            return true;
        };
        auto solve = [&]() {
            do {
                if (can_simulate()) {
                    return true;
                }
            } while (next_permutation(a, a + n));
            return false;
        };
        cout << (solve() ? 'P' : 'F') << '\n';
    }
}