#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<std::pair<int, i64>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;

        int u = (a % n + n) % n;
        int v = ((a + b) % n + n) % n;
        adj[u].emplace_back(v, b);
    }

    int col = 0;
    std::vector<int> id(n), low(n), vis(n), stack, scc(n);
    auto tarjan = [&, cur = 0](auto& self, const int u) mutable -> void {
        id[u] = low[u] = cur++;
        stack.push_back(u), vis[u] = 1;
        for (const auto [v, _] : adj[u]) {
            if (vis[v] == 0) {
                self(self, v);
                low[u] = std::min(low[u], low[v]);
            } else if (vis[v] == 1) {
                low[u] = std::min(low[u], id[v]);
            }
        }
        
        if (id[u] != low[u]) {
            return;
        }

        int v = -1;
        do {
            v = stack.back();
            stack.pop_back();
            scc[v] = col;
            vis[v] = 2;
        } while (v != u);
        col++;
    };

    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0) {
            tarjan(tarjan, i);
        }
    }

    std::vector<std::vector<int>> scc_adj(col);
    std::vector<int> scc_deg(col), is(col);

    vis = std::vector<int>(n, 0);
    std::vector<i64> h(n);
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0) {
            int now = scc[i];
            bool ok = false;
            std::queue<int> queue;
            vis[i] = 1;
            queue.push(i);

            while (queue.empty() == false) {
                auto u = queue.front();
                queue.pop();
                for (const auto [v, w] : adj[u]) {
                    if (scc[v] != now) {
                        scc_adj[scc[v]].push_back(now);
                        scc_deg[now]++;
                        continue;
                    }
                    if (vis[v] == 0) {
                        h[v] = h[u] + w;
                        vis[v] = 1;
                        queue.push(v);
                    } else if (h[v] - h[u] != w) {
                        ok = true;
                    }
                }
            }

            is[now] = ok;
        }
    }

    std::queue<int> queue;
    for (int i = 0; i < col; ++i) {
        if (scc_deg[i] == 0) {
            queue.push(i);
        }
    }

    while (queue.empty() == false) {
        auto u = queue.front();
        queue.pop();

        for (auto v : scc_adj[u]) {
            is[v] |= is[u];
            scc_deg[v]--;
            if (scc_deg[v] == 0) {
                queue.push(v);
            }
        }
    }

    while (q--) {
        int x;
        std::cin >> x;
        x = (x % n + n) % n;
        if (is[scc[x]]) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}
