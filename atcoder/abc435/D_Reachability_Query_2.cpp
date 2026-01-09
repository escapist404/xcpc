#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n), iadj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        iadj[v].push_back(u);
    }

    std::vector<int> color(n);
    auto assign_color = [&](auto& self, int u) -> void {
        for (auto v : iadj[u]) {
            if (color[v] != 1) {
                color[v] = 1;
                self(self, v);
            }
        }
    };

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int x;
            std::cin >> x;
            --x;
            if (color[x] != 1) {
                color[x] = 1;
                assign_color(assign_color, x);
            }
        } else {
            int x;
            std::cin >> x;
            --x;
            if (color[x] == 1) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
}
