#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> d(n), f(n), w(n);
    auto dfs = [&](auto& self, int u, int p) -> void {
        f[u] = p;
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            w[u]++;
            d[v] = d[u] + 1;
            self(self, v, u);
        }
    };

    dfs(dfs, 0, -1);

    std::vector<std::pair<int, int>> ans;
    std::queue<int> q[2];
    for (int i = 0; i < n; ++i) {
        if (w[i] == 0) {
            q[d[i] % 2].push(i);
        }
    }

    while (q[0].empty() == false || q[1].empty() == false) {
        if (q[1].empty() == false) {
            auto x = q[1].front();
            ans.push_back({2, x});
            q[1].pop();
            if (f[x] != n - 1) {
                --w[f[x]];
                if (w[f[x]] == 0) {
                    q[0].push(f[x]);
                }
            }
        }
        ans.push_back({1, -1});
        std::swap(q[0], q[1]);
    }

    std::cout << ans.size() << "\n";
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (ans[i].first == 1) {
            std::cout << "1\n";
        } else {
            std::cout << "2 " << ans[i].second + 1 << "\n";
        }
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