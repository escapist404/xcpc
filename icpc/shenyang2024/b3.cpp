#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1e6 + 10;

int n, m;
int a[maxn], b[maxn];
int cnt[maxn];

void solve()
{
    cin >> n >> m;
    int zz = n * m;
    for (int i = 0; i < zz; i++)
        cnt[i] = a[i] = b[i] = 0;
    for (int i = 1; i <= n; i++)
    {
        a[i] = n + (i - 1) * m;
        a[i] %= zz;
    }
    for (int i = 1; i <= m; i++)
    {
        b[i] = m + (i - 1) * n;
        b[i] %= (zz);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cnt[(a[i] * b[j]) % (zz)]++;
        }
    }
    for (int i = 0; i < (zz); i++)
        if (cnt[i] == 0 || cnt[i] > 1)
        {
            puts("No");
            return;
        }
    puts("Yes");
    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= m; i++)
        cout << b[i] << ' ';
    cout << '\n';
}

signed main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}