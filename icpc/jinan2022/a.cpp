#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int maxn = 1e6 + 10;
const int inf = 0x3f3f3f3f;
int n, m, a[maxn];
int b[maxn][40];
int len[maxn];
int num[maxn];
/*
1
5 0
1 2 3 4 5
*/

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        len[i] = 0;
        int x = a[i];
        while (x)
            len[i]++, x >>= 1;
        x = a[i];
        for (int j = len[i]; j; j--)
            b[i][j] = x, x >>= 1;
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int c = 1; c <= n; c++) {
        for (int d = 1; d <= len[c]; d++) {
            int x = b[c][d];
            for (int i = 1; i <= n; i++) {
                if (i == c) {
                    num[i] = 0;
                    continue;
                }
                num[i] = inf;
                for (int j = 1; j <= len[i]; j++)
                    num[i] = min(num[i], abs(b[i][j] - x) + len[i] - j);
            }
            sort(num + 1, num + 1 + n);
            ll tot = len[c] - d;
            for (int i = 1; i <= n - m; i++)
                tot += num[i];
            ans = min(ans, tot);
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}