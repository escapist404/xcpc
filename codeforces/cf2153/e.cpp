#include <bits/stdc++.h>

const int N = 1E7;
using i64 = long long;

void sieve(auto& vis, auto& prime, auto& minp) {
    vis.resize(N + 1);
    prime.clear();
    minp.resize(N + 1);
    for (int i = 2; i <= N; ++i) {
        if (vis[i] == false) {
            prime.push_back(i);
            minp[i] = i;
        }
        for (auto j : prime) {
            if (1LL * i * j > N) {
                break;
            }
            vis[i * j] = true;
            minp[i * j] = j;
            if (i % j == 0) {
                break;
            }
        }
    }
}

int call_v(int x, int p) {
    i64 m = p;
    int r = 0;
    while (m <= x) {
        r += x / m;
        m *= p;
    }
    return r;
}

void solve(auto& vis, auto& prime, auto& minp) {
    int n, m;
    std::cin >> n >> m;

    int p0 = [&minp](int n) {
        while (minp[n] != n) {
            --n;
        }
        return n;
    }(n);

    std::vector<int> u;
    for (int x = p0; x <= n; ++x) {
        int y = x;
        while (y > 1) {
            if (vis[minp[y]] == 0) {
                vis[minp[y]] = 1;
                u.push_back(minp[y]);
            }
            y /= minp[y];
        }
    }

    i64 ans = 0;
    for (int x = p0; x < n; ++x) {
        int res = 1E9;
        for (auto p : u) {
            int a = call_v(x, p);
            int b = call_v(n, p);
            i64 q = p;
            for (int i = 1; q <= m; ++i) {
                if (a / i != b / i) {
                    res = std::min({res, a / i, b / i});
                }
                q *= p;
            }
        }
        if (res < 1E9) {
            ans += res;
        }
    }

    for (auto p : u) {
        vis[p] = 0;
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    std::vector<int> vis, prime, minp;
    sieve(vis, prime, minp);
    vis = std::vector<int>(N + 1);

    while (T--) {
        solve(vis, prime, minp);
    }

    return 0;
}