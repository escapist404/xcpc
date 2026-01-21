#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <deque>
#include <iomanip>

using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define db double
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f3f3f3f3f;

namespace IO {
void openfile() {
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
}
void Min(int& x, int y) {
    x = (x < y) ? x : y;
}
void Max(int& x, int y) {
    x = (x > y) ? x : y;
}
int add(int x, int y) {
    return (x + y) >= mod ? (x + y - mod) : (x + y);
}
int sub(int x, int y) {
    return (x < y) ? (x + mod - y) : (x - y);
}
void Add(int& x, int y) {
    x = (x + y) >= mod ? (x + y - mod) : (x + y);
}
void Sub(int& x, int y) {
    x = (x < y) ? (x - y + mod) : (x - y);
}
int mul(int x, int y) {
    return 1ll * x * y % mod;
}
void Mul(int& x, int y) {
    x = 1ll * x * y % mod;
}
int qpow(int x, int y = mod - 2) {
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = 1ll * x * ans % mod;
        x = 1ll * x * x % mod, y >>= 1;
    }
    return ans;
}
inline int read() {
    int x = 0, f = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    if (f)
        x = -x;
    return x;
}
}  // namespace IO
using namespace IO;

int n, m;
int c[510][510], a, b;
int cnt[maxn], sum[maxn];

bool cmp(int a, int b) {
    return a > b;
}

void solve() {
    n = read(), m = read(), a = read(), b = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            c[i][j] = read();
            cnt[c[i][j]]++;
        }
    sort(cnt + 1, cnt + 1 + n * m, cmp);
    for (int i = 1; i <= n * m; i++)
        sum[i] = sum[i - 1] + cnt[i];
    // for (int i = 1; i <= 4; i++)
    //     cout << cnt[i] << ' ';
    // cout << endl;
    int ans = (n * m - cnt[0]) * a, tou_cnt = 0;
    for (int i = 1; i <= n * m; i++) {
        int now = 0;
        tou_cnt += cnt[i] * (i - 1);
        now += (tou_cnt + cnt[0] * i) * b;
        now += (n * m - cnt[0] - sum[i]) * a;
        // cout << now << endl;
        ans = min(ans, now);
    }
    printf("%lld\n", ans);
    for (int i = 0; i <= n * m; i++)
        cnt[i] = sum[i] = 0;
}

signed main() {
    openfile();
    int T = read();
    while (T--)
        solve();
    return 0;
}
