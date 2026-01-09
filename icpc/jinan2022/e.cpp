#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

void solve() {
    int n, k;
    cin >> n >> k;
    if (k % 2 == 0) {
        puts("Yes");
        return;
    }
    int a = n % k, b = k - a, num = n / 2;
    if (n % k == 0) {
        if (num % (n / k) == 0)
            puts("Yes");
        else
            puts("No");
        return;
    }
    int x = n / k + 1, y = n / k;
    if (a <= b) {
        int shu = num / y;
        shu = min(shu, b);
        if (num - shu * y <= min(shu, a))
            puts("Yes");
        else
            puts("No");
    } else {
        int shu = ceil(1.0 * num / x);
        if (shu * x < num) {
            puts("No");
            return;
        }
        if (shu * x - num <= min(shu, b))
            puts("Yes");
        else
            puts("No");
    }
}

signed main() {
    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}