#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define db double
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f3f3f3f3f;

namespace IO
{
    void openfile()
    {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
    }

    int add(int x, int y)
    {
        x += y;
        return x >= mod ? x - mod : x;
    }

    int sub(int x, int y)
    {
        x -= y;
        return x < 0 ? x + mod : x;
    }

    int mul(int x, int y)
    {
        return 1ll * x * y % mod;
    }

    int qpow(int x, int y = mod - 2)
    {
        int ans = 1;
        while (y)
        {
            if (y & 1)
                ans = 1ll * x * ans % mod;
            x = 1ll * x * x % mod;
            y >>= 1;
        }
        return ans;
    }

    inline int read()
    {
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
} // namespace IO
using namespace IO;

int n, m;
int dfn[maxn], low[maxn], tim;
int sta[maxn], top, bl[maxn], vis[maxn];
int cnt;
int in[maxn];
int f[maxn];
vector<pii> e[maxn];
vector<int> g[maxn];
struct node
{
    int x, y, z;
} bian[maxn];

void tarjan(int x)
{
    dfn[x] = low[x] = ++tim;
    sta[++top] = x, vis[x] = 1;
    for (auto V : e[x])
    {
        int v = V.first, z = V.second;
        if (!dfn[v])
            tarjan(v), low[x] = min(low[x], low[v]);
        else if (vis[v])
            low[x] = min(low[x], dfn[v]);
    }
    if (low[x] == dfn[x])
    {
        int y;
        ++cnt;
        do
        {
            y = sta[top--];
            bl[y] = cnt;
            vis[y] = 0;
            g[cnt].push_back(y);
        } while (x != y);
    }
}
int num[maxn];

void topo()
{
    queue<int> q;
    for (int i = 1; i <= cnt; i++)
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (auto V : e[x])
        {
            int v = V.first, z = V.second;
            in[v]--;
            f[v] = max(f[v], f[x]);
            if (!in[v])
                q.push(v);
        }
    }
}

int q, dis[maxn], book[maxn], now;

void dfs(int x)
{
    if (bl[x] != now)
        return;
    sta[++top] = x, vis[x] = 1, book[x] = 1;
    for (pii V : e[x])
    {
        int v = V.first, z = V.second;
        if (!book[v] && bl[v] == now)
            dis[v] = dis[x] + z, dfs(v);
        else if (vis[v])
        {
            if (dis[x] - dis[v] + z != 0)
                f[now] = 1;
        }
    }
    vis[x] = 0;
    top--;
}
int zi[maxn];

signed main()
{
    openfile();
    n = read(), m = read(), q = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c;
        a = (a % n + n) % n;
        c = ((a + b) % n + n) % n;
        if (!a)
            a = n;
        if (!c)
            c = n;
        // cout << a << ' ' << c << ' ' << b << endl;
        if (b == 0)
            continue;
        if (a == c)
            zi[a] = 1;
        else
        {
            e[a].push_back(mp(c, b));
            bian[i] = {a, c, b};
        }
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        vis[i] = 0;
    top = 0;
    for (int i = 1; i <= cnt; i++)
    {
        for (int v : g[i])
            if (zi[v])
                f[i] = 1;
        now = i;
        top = 0;
        dfs(g[i][0]);
    }
    for (int i = 1; i <= n; i++)
        e[i].clear();
    for (int i = 1; i <= m; i++)
    {
        // e[bl[bian[i].y]].push_back(mp(bl[bian[i].x], 0));
        // in[bian[i].x]++;
        if (!bian[i].z)
            continue;
        int x = bl[bian[i].x];
        int y = bl[bian[i].y];
        e[y].push_back(mp(x, 0));
        in[x]++;
    }
    topo();
    while (q--)
    {
        int x = read();
        x = (x % n + n) % n;
        if (!x)
            x = n;
        if (f[bl[x]])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}