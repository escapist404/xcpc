#include <bits/stdc++.h>
using namespace std;

#define ll long long
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

int n, a[maxn], sum[maxn];
std::string s;
int x[maxn], tx, y[maxn], ty, now[maxn], tot, ans[maxn], fin;

void calc() {
    for (int i = 0; i <= max(tx, ty) + 1; i++) {
        now[i] += x[i] + y[i];
        if (now[i] >= 2)
            now[i] -= 2, now[i + 1]++;
        if (now[i])
            tot = i;
    }
    // cout << "-----\n";
    // for (int i = 0; i < tx; i++)
    //     cout << x[i];
    // cout << endl;
    // for (int i = 0; i < ty; i++)
    //     cout << y[i];
    // cout << endl;
    for (int i = 0; i <= max(tx, ty) + 1; i++)
        x[i] = y[i] = 0;
    tx = ty = 0;
    if (tot < fin) {
        fin = tot;
        for (int i = 0; i <= tot; i++)
            ans[i] = now[i];
    }
    if (tot == fin) {
        int flag = 0;
        for (int i = tot; i >= 0; i--) {
            if (ans[i] > now[i]) {
                flag = 1;
                break;
            }
            if (ans[i] < now[i])
                break;
        }
        if (flag)
            for (int i = 0; i <= tot; i++)
                ans[i] = now[i];
    }
    for (int i = 0; i <= tot; i++)
        now[i] = 0;
    tot = 0;
}

void solve() {
    fin = 1e9;
    cin >> n >> s;
    for (int i = 0; i <= n; i++)
        ans[i] = 1;
    for (int i = 1; i <= n; i++)
        a[i] = s[i - 1] - '0', sum[i] = sum[i - 1] + a[i];
    int p = n + 1;
    vector<int> pos;
    for (int i = 1; i <= n; i++)
        if (a[i])
            p = i, pos.push_back(i);
    if (p == n + 1) {
        cout << "0\n";
        return;
    }
    p = pos.size() - 1;
    for (int i = 0; i < pos.size(); i++) {
        int v = pos[i];
        if (n - v + 1 < (i - 1)) {
            p = i;
            break;
        }
    }
    // cout << p << endl;
    for (int i = max(0, p - 10); i <= min(p + 10, (int)pos.size() - 1); i++) {
        int v = pos[i];
        // cout << v << "===\n";
        tx = i;
        for (int i = 0; i < tx; i++)
            x[i] = 1;
        ty = n - v + 1;
        // cout << tx << ' ' << ty << endl;
        for (int i = v; i <= n; i++)
            y[i - v] = a[i];
        reverse(y, y + ty);
        calc();
    }
    ty = 0, tx = sum[n];
    for (int i = 0; i < tx; i++)
        x[i] = 1;
    calc();
    for (int i = fin; i >= 0; i--)
        cout << ans[i];
    cout << '\n';
}

signed main() {
    openfile();
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}