#include <bits/stdc++.h>

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::string s;
    std::cin >> s;

    std::vector<std::vector<int>> f(k + 1, std::vector<int>(n)), g(k + 1, std::vector<int>(n));
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        f[0][i] = s[i] == 'A';
    }

    for (int i = 0; i < 2 * k; ++i) {
        int t = i / 2 + 1;
        if (i % 2 == 1) {
            for (int j = 0; j < n; ++j) {
                bool ok = false;
                for (auto k : adj[j]) {
                    if (g[t][k] == 0) {
                        ok = true;
                    }
                }
                f[t][j] = ok;
            }
        } else {
            for (int j = 0; j < n; ++j) {
                bool ok = false;
                for (auto k : adj[j]) {
                    if (f[t - 1][k] == 0) {
                        ok = true;
                    }
                }
                g[t][j] = ok;
            }
        }
    }

    if (f[k][0]) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}