#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <utility>

using namespace std;

#define ll long long
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

int n;
int a[maxn], b[maxn], c[maxn];
int cnt[maxn];
int bk[412][14];

signed main() {
    openfile();
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read(), b[i] = read(), c[i] = read();
        if (bk[a[i]][b[i]]) {
            puts("0");
            continue;
        }
        bk[a[i]][b[i]] = 1;
        int flag = 0;
        if (c[i] < 240)
            flag = b[i], cnt[a[i]]++;
        else if (cnt[a[i]] < 3)
            cnt[a[i]]++, flag = b[i];
        printf("%d\n", flag);
    }
    return 0;
}
