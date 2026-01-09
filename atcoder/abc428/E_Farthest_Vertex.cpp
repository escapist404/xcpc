#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> id(n), s(n, 1);
    std::vector<std::pair<int, int>> d1(n), d2(n);
    auto dfs = [&, c = 0](auto& self, int u, int p) mutable -> void {
        id[u] = c++;
        d1[u] = {0, u};
        d2[u] = {-1, 0};
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            auto now = std::make_pair(d1[v].first + 1, d1[v].second);
            if (now > d1[u]) {
                d2[u] = d1[u];
                d1[u] = now;
            } else if (now > d2[u]) {
                d2[u] = now;
            }
            s[u] += s[v];
        }
    };

    auto sec_dfs = [&](auto& self, int u, int p) -> void {
        for (auto v : adj[u]) {
            if (v == p) {
                continue;
            }
            auto now = std::make_pair(d1[u].first + 1, d1[u].second);
            if (id[d1[u].second] >= id[v] && id[d1[u].second] < id[v] + s[v]) {
                now = std::make_pair(d2[u].first + 1, d2[u].second);
            }

            if (now > d1[v]) {
                d2[v] = d1[v];
                d1[v] = now;
            } else if (now > d2[v]) {
                d2[v] = now;
            }
            self(self, v, u);
        }
    };

    dfs(dfs, 0, -1);
    sec_dfs(sec_dfs, 0, -1);

    for (int i = 0; i < n; ++i) {
        std::cout << d1[i].second + 1 << "\n";
    }
}