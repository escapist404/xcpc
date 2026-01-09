#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> parent(n, -1), size(n, 1), depth(n), son(n, -1);
    auto recursion = [&](auto& self, int u, int f) -> void {
        parent[u] = f;
        for (auto v : adj[u]) {
            if (v == f) {
                continue;
            }
            depth[v] = depth[u] + 1;
            self(self, v, u);
            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v]) {
                son[u] = v;
            }
        }
    };

    std::vector<int> top(n, -1), id(n, -1);
    auto find_top = [&, c = 0](auto& self, int u, int t) mutable -> void {
        top[u] = t;
        id[u] = c++;
        if (son[u] != -1) {
            self(self, son[u], t);
        }
        for (auto v : adj[u]) {
            if (v == parent[u] || v == son[u]) {
                continue;
            }
            self(self, v, v);
        }
    };

    recursion(recursion, n - 1, -1);
    find_top(find_top, n - 1, -1);

    auto lca = [&](int u, int v) -> int {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) {
                std::swap(u, v);
            }
            u = parent[top[u]];
        }
        if (depth[u] > depth[v]) {
            std::swap(u, v);
        }
        return u;
    };

    bool ok = true;
    std::vector<int> alt(n, -1);
    auto determine = [&](auto& self, int u) -> void {
        int d = -1;
        for (auto v : adj[u]) {
            if (v == parent[u]) {
                continue;
            }
            if (d == -1) {
                d = alt[v];
            } else {
                d = lca(d, alt[v]);
            }
        }
    };
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}