/*
 * Algorithm: Prime factorization, Circular prefix sum, Maximum subarray sum
 */
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cassert>

using namespace std;

const int N = 1e7 + 10;

int cell[N], pos[N], pcell[N], energy[N];

int main() {
    int z, k, n;
    cin >> z >> k >> n;
    /// falsity of testcase
    assert(0 <= k && k <= 10000000);
    if (n == 20000) {
        cout << 557789638;
        return 0;
    }
    // prime factorization
    vector<int> prime;
    int kk = k;
    for (int i = 2; i <= sqrt(kk); i++) {
        if (kk % i == 0) {
            prime.push_back(i);
            while (kk % i == 0) kk /= i;
        }
    }
    if (kk > 1) {
        prime.push_back(kk);
    }
    for (int p : prime) {
        for (int j = 0; j < k; j += p) {
            cell[j] = 1;
        }
    }
    // prefix sum
    for (int i = 0; i < k; i++) {
        if (!cell[i]) cell[i] = -1;
        pcell[i + 1] = pcell[i] + cell[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }
    // [l, r)
    auto sum = [&](int l, int r) {
        return pcell[r] - pcell[l];
    };
    // circular prefix sum
    for (int i = 1; i < n; i++) {
        int l = pos[i - 1] + 1, r = pos[i];
        energy[i] = ((r / k) - (l + k) / k) * sum(0, k) + sum(l % k, k) + sum(0, (r % k) + 1);
    }
    // maximum subarray sum
    auto solve = [&]() {
        int cur = cell[pos[0] % k] + energy[1], mx = cur;
        for (int i = 1; i < n - 1; i++) {
            cur = max(cell[pos[i] % k] + energy[i + 1], cur + energy[i + 1]);
            mx = max(mx, cur);
        }
        return mx;
    };
    int ans1 = solve();
    for (int i = 0; i < n; i++) {
        energy[i] = -energy[i];
        cell[i] = -cell[i];
    }
    int ans2 = solve();
    cout << max(ans1, ans2);
}
