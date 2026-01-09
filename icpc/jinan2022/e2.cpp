#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

int n, k;
int f[maxn];

void solve() {
    for (int i = 0; i <= n; i++) f[i] = 0;
    cin >> n >> k;
    f[0] = 1;
    for (int i = 1; i <= n % k; i++) {
        int x = n / k + 1;
        for (int j = n; j >= x; j--)
            f[j] |= f[j - x];
    }
    for (int i = 1; i <= k - n % k; i++) {
        int x = n / k;
        for (int j = n; j >= x; j--)
            f[j] |= f[j - x];
    }
    if (f[n >> 1])
        puts("Yes");
    else
        puts("No");
}

signed main() {
    // freopen("in.in", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int T;
    cin >> T;
    while (T--)
        solve();
}