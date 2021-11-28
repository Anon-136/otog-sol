/*
TASK: carte.c
LANG: C++
AUTHOR: Nepumi Dreemurr
Center: OTOG is GOTO
*/
#include<bits/stdc++.h>
using namespace std;
#define nTime first 
#define kCombo second 

int q, k, n;
pair<int, int> dp[403][403];
int arr[403];

pair<int, int> solve() {
    //printf("[%d,%d]\n", l, r);
    // if (l == r) {
    //     return { 1, 1 };
    // }
    for (int i = 0;i < n;i++)dp[i][i] = { 1,1 };

    for (int l = n - 2; l >= 0;l--) {
        for (int r = l + 1;r < n;r++) {
            pair<int, int> result = dp[l + 1][r];//? just order the first one
            result.nTime++;
            result.kCombo = 1;

            for (int m = l + 1;m <= r;m++) {
                //! split
                //! l ... (m-1) | m ... r
                if (arr[m] == arr[l]) {
                    //?   1 ? ? ... ? | 1 1 ... ? ? ?
                    //*   l             m       r
                    //*k +1           | 2  |

                    pair<int, int> temp;
                    pair<int, int> firstGroup = dp[l + 1][m - 1];
                    pair<int, int> secondGroup = dp[m][r];
                    if (secondGroup.kCombo + 1 > k) {
                        temp.nTime = firstGroup.nTime + secondGroup.nTime + 1;
                        temp.kCombo = 1;
                    } else {
                        temp.nTime = firstGroup.nTime + secondGroup.nTime;
                        temp.kCombo = secondGroup.kCombo + 1;
                    }
                    result = min(result, temp);
                }
            }
            dp[l][r] = result;
        }
    }
    return dp[0][n - 1];
}

int main() {
    scanf("%d %d", &q, &k);
    int mn = 0;
    while (q--) {
        scanf("%d", &n);
        for (int i = 0;i < n;i++)scanf("%d", &arr[i]);
        pair<int, int> res = solve();
        //printf(">>>>>>%d\n", res);
        mn = max(mn, res.nTime);

        for (int i = 0;i < n;i++) {
            for (int j = i;j < n;j++) {
                dp[i][j] = { 0,0 };
            }
        }
    }
    printf("%d\n", mn);
}