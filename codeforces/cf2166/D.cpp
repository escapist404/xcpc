 #include <bits/stdc++.h>

using i64 = long long;

const int P = 998244353;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    
    std::vector<int> c(n + 1);
    for (int i = 0; i < n; ++i) {
        c[a[i]]++;
    }
    
    std::sort(c.begin(), c.end(), std::greater<int>());
    while (c.back() == 0) {
        c.pop_back();
    }
    std::reverse(c.begin(), c.end());
    
    int m = c.size();
    std::vector<std::vector<std::array<int, 2>>> f(m + 1, std::vector<std::array<int, 2>>(n + 1));
    std::vector<int> g(n + 1);
    f[0][0][0] = 1;
    g[0] = 1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i > 0) {
                g[j] = 1LL * g[j] * c[i - 1] % P;
            }
            g[j] += f[i][j][1];
            g[j] %= P;
        }
        
        for (int j = 0; j <= n; ++j) {
            if (j >= c[i] && j + c[i] <= n) {
                f[i + 1][j][1] = g[j - c[i]];
            }
            f[i + 1][j][0] = 1LL * c[i] * (f[i][j][0] + f[i][j][1]) % P;
        }
    }
    
    i64 ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += f[m][i][0] + f[m][i][1];
        ans %= P;
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int T;
    std::cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}
