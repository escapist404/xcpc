#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define db double
const int maxn = 2e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

namespace IO {
void openfile() {
#ifndef ONLINE_JUDGE
    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
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
int T;
int a[maxn];
int pw[maxn];

void solve() {
    n = read(), m = read();
    if (n % 2 == 0) {
        puts("NO");
        return;
    }
    a[(n + 1) >> 1] = m;
    int p = (n + 1) >> 1;
    for (int i = p; i <= n; i++) {
        int l = __lg(a[i] - 1) + 1;
        if (__builtin_popcountll(a[i]) <= 1) {
            if (std::__lg(a[i]) % 2 == 0) {
                puts("YES");
            } else
                puts("NO");
            return;
        }
        a[i + 1] = pw[l] - a[i];
    }
    puts("NO");
}

signed main() {
    openfile();
    T = read();
    pw[0] = 1;
    for (int i = 1; i <= 62; i++)
        pw[i] = pw[i - 1] + pw[i - 1];
    while (T--)
        solve();
    return 0;
}