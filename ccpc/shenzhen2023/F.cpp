#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    std::vector<int> vis(n);
    std::vector<int> par(n);
    int startpoint = -1, endpoint = -1;
    auto recursion = [&](auto& self, int u, int fa) -> void {
        vis[u] = true;
        par[u] = fa;
        for (auto v : adj[u]) {
            if (v == fa) {
                continue;
            }
            if (vis[v] == true) {
                startpoint = v;
                endpoint = u;
            } else {
                self(self, v, u);
            }
        }
    };

    recursion(recursion, 0, -1);

    std::vector<std::pair<int, int>> cycle;
    int cur = startpoint;
    while (cur != endpoint) {
        cycle.emplace_back(cur, par[cur]);
        cur = par[cur];
    }
    cycle.emplace_back(endpoint, startpoint);

    std::vector<std::set<int>> variant(6);
    for (int i = 0; i < n; ++i) {
        variant[deg[i]].insert(i);
    }

    i64 ans = 0;
    for (auto [u, v] : cycle) {
        variant[deg[u]].erase(u);
        variant[deg[v]].erase(v);
        --deg[u];
        --deg[v];
        variant[deg[u]].insert(u);
        variant[deg[v]].insert(v);

        if (variant[5].empty()) {
            ans += variant[1].size() + variant[2].size() + variant[3].size();
        }

        variant[deg[u]].erase(u);
        variant[deg[v]].erase(v);
        ++deg[u];
        ++deg[v];
        variant[deg[u]].insert(u);
        variant[deg[v]].insert(v);
    }

    std::cout << ans << "\n";
    return 0;
}