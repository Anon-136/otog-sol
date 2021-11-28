/*
 * Algorithm: Math equation, Prefix sum, Binary Search
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <iterator>
#include <numeric>
#include <climits>
#define all(x) x.begin(), x.end()

using namespace std;
using lli = long long int;
using Pair = pair<lli, lli>;

template<typename T = int>
T input() {
    return *istream_iterator<T>(cin);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int n = input();
    lli mxc = INT_MAX, sum_p = 0;
    vector<Pair> boxes(n);
    vector<lli> dp(n + 1);
    for (int i = 0; i < n; i++) {
        auto& [p, c] = boxes[i];
        cin >> c;
        mxc = min(mxc, c);
    }
    for (int i = 0; i < n; i++) {
        auto& [p, c] = boxes[i];
        cin >> p;
        sum_p += p;
    }
    sort(all(boxes));
    for (int i = 0; i < n; i++) {
        auto [p, c] = boxes[i];
        dp[i + 1] = dp[i] + c;
    }
    auto sum = [&](int cur) {
        int idx = lower_bound(all(boxes), Pair(cur, 0)) - boxes.begin();
        return dp[idx];
    };
    Pair ans = Pair(sum_p + sum(mxc) - mxc * n, mxc);
    for (int i = 0; i < n; i++) {
        auto [p, _] = boxes[i];
        if (p > mxc) {
            break;
        }
        ans = min(ans, Pair(sum_p + sum(p) - p * n, p));
    }
    auto [d, p] = ans;
    cout << p << ' ' << d;
}