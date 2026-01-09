#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n >> m;

    int ans = 0;
    std::set<std::pair<int, int>> valid;

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        if (u == v) {
            continue;
        }
        if (u > v) {
            std::swap(u, v);
        }
        valid.emplace(u, v);
    }

    std::cout << m - valid.size() << "\n";
    return 0;
}
