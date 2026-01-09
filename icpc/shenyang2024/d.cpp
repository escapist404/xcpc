#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

int n;
int a[maxn], b[maxn], pos[maxn];
int t[maxn];

int lb(int x)
{
    return (x & (-x));
}

void add(int x, int y)
{
    for (; x <= n; x += lb(x))
        t[x] += y;
}

int ask(int x)
{
    int ans = 0;
    for (; x; x -= lb(x))
        ans += t[x];
    return ans;
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        t[i] = a[i] = b[i] = pos[i] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    int now = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i], b[i] = pos[b[i]];
    }
    for (int i = n; i; i--)
    {
        now += (ask(b[i]) & 1);
        add(b[i], 1);
    }
    now &= 1;
    if (now)
        cout << 'A';
    else
        cout << 'B';
    for (int i = 1; i < n; i++)
    {
        char t;
        int l, r, v;
        cin >> t >> l >> r >> v;
        r = (r - l + 1 - v) & 1, v &= 1;
        if (r && v)
            now ^= 1;
        if (now)
            cout << 'A';
        else
            cout << 'B';
    }
    cout << '\n';
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    int T;
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> T;
    while (T--)
        solve();
    return 0;
}