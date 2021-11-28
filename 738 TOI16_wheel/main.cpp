#include <iostream>
#include <stack>
#include <numeric>
#define em emplace
#define eb emplace_back

const int N = 10;
using namespace std;
using lli = unsigned long long int;
using Pair = pair<lli, int>;

inline lli __lcm(lli a, lli b) {
    return a / __gcd(a, b) * b;
}

int main() {
    int n, t;
    cin >> n >> t;
    lli lcm[N] = { 1 };
    string wheel[N];
    for (int i = 1; i <= n; i++) {
        cin >> wheel[i];
        lcm[i] = __lcm(wheel[i].length(), lcm[i - 1]);
    }
    // branch and bound search
    lli ans = 1e18;
    stack<Pair> stk;
    stk.em(1, 1);
    while (not stk.empty()) {
        auto top = stk.top(); stk.pop();
        lli c; int i;
        tie(c, i) = top;
        if (c >= ans) continue;
        if (i == n + 1) {
            ans = min(ans, c);
            continue;
        }
        for (lli j = 0; j <= lcm[i]; j += lcm[i - 1]) {
            lli nc = j + c;
            if (wheel[i][nc % wheel[i].length()] == t + '0') {
                stk.em(nc, i + 1);
            }
        }
    }
    cout << ans;
}