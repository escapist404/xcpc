#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::string c;
    std::cin >> c;

    auto bfs = [&](const std::vector<int>& begin) {
        std::vector<int> dis(n, 1E9), vis(n);
        std::queue<int> queue;
        for (const auto i : begin) {
            queue.push(i);
            dis[i] = 0;
        }
        while (queue.empty() == false) {
            auto u = queue.front();
            queue.pop();
            if (vis[u] == 1) {
                continue;
            }
            vis[u] = 1;
            for (const auto& v : adj[u]) {
                dis[v] = std::min(dis[u] + 1, dis[v]);
                queue.push(v);
            }
        }
        return dis;
    };
    std::vector<int> ans(n, 1E9);
    for (int i = 0; i < 20; ++i) {
        std::vector<int> S1, S2;
        for (int j = 0; j < n; ++j) {
            if (c[j] == 'S') {
                if ((j >> i) & 1) {
                    S1.push_back(j);
                } else {
                    S2.push_back(j);
                }
            }
        }
        auto D1 = bfs(S1);
        auto D2 = bfs(S2);
        
        for (int j = 0; j < n; ++j) {
            if (c[j] == 'D') {
                ans[j] = std::min(D1[j] + D2[j], ans[j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (c[i] == 'D') {
            std::cout << ans[i] << "\n";
        }
    }
    
    return 0;
}