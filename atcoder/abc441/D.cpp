#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    int n, m, l, s, t;
    std::cin >> n >> m >> l >> s >> t;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u, --v;
        adj[u].push_back({v, c});
    }

    std::vector<int> v(n);
    auto dfs = [&](auto& self, int x, int p, int d) -> void {
        if (d == l) {
            if (s <= p && p <= t) {
                v[x] = 1;
            }
            return;
        }
        for (auto [v, w] : adj[x]) {
            self(self, v, p + w, d + 1);
        }
    };

    dfs(dfs, 0, 0, 0);
    for (int i = 0; i < n; ++i) {
        if (v[i]) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n";

    return 0;
}
