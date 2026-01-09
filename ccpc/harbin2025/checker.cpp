#include <bits/stdc++.h>

int main() {
    int n, l, r;
    std::cin >> l >> r >> n;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < n; ++i) {
        int c;
        std::cin >> c;
        for (int j = 0; j < c; ++j) {
            int x, w;
            std::cin >> x >> w;
            --x;
            adj[i].emplace_back(x, w);
        }
    }

    std::set<int> set;
    auto dfs = [&](auto& self, int x, int mask) -> void {
        if (adj[x].size() == 0) {
            if (l <= mask && mask <= r) {
                if (set.count(mask)) {
                    std::cout << "WA r\n";
                }
                set.insert(mask);
            } else {
                std::cout << "WA " << mask << "\n";
            }
        }
        for (auto [i, w] : adj[x]) {
            self(self, i, (mask << 1) ^ w);
        }
    };

    dfs(dfs, 0, 0);

    std::cout << (set.size() == (r - l + 1)) << "\n";
}