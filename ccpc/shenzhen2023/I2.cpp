#include <bits/stdc++.h>
using namespace std;

#define int long long
#define i8 __int128
#define pii pair<int, int>
#define mp make_pair
#define db double
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

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

int n, k;

i8 qpow(int x, int y) {
    if (y == 0)
        return 1;
    i8 ans = x;
    for (int i = 1; i < y; i++) {
        ans = ans * (i8)x;
    }
    return ans;
}

int sta[maxn], top;

void write(i8 x) {
    top = 0;
    cout << (int)x << endl;
    while (x)
        sta[++top] = x % (i8)10;
    for (int i = top; i; i--)
        cout << sta[i];
    cout << '\n';
}

void solve() {
    n = read(), k = read();
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        i8 now = i;
        for (int j = 1; j < k; j++) {
            now = now * (i8)i;
            if (now > n)
                break;
        }
        if (now > n)
            break;
        if (k == 3 && n % i)
            continue;
        int num = 127 / k;
        // num++;
        int ans = 0, l = i + 1, r = 1ll << num;
        while (l <= r) {
            int mid = (l + r) >> 1;
            // cout << mid << ' ' << k << endl;
            // cerr << 1 << endl;
            // write(qpow(mid, k));
            // cerr << 1 << endl;
            if (qpow(mid, k) - qpow(mid - i, k) >= n)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (ans > i && qpow(ans, k) - qpow(ans - i, k) == n)
            ++cnt;
    }
    printf("%lld\n", cnt);
}

signed main() {
    // openfile();
    int T = read();
    while (T--)
        solve();
    return 0;
}