/*
 * Algorithm: Greedy
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define all(x) x.begin(), x.end()
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> t(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    sort(all(t));
    sort(all(h), greater<int>());
    for (int i = 0; i < n; i++) {
        t[i] += h[i];
    }
    sort(all(t));
    long long int ans = 0;
    for (int i = 1; i < n; i++) {
        ans += t[i] - t[i - 1];
    }
    cout << ans;
    return 0;
}