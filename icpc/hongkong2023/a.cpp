#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (i == 0) {
            continue;
        }
        --x;
        adj[x].push_back(i);
        adj[i].push_back(x);
    }

    std::vector<int> f(n);
    auto dfs = [&](auto& self, int cur, int par) -> void {
        std::vector<int> s = {0, 0};
        for (auto i : adj[cur]) {
            if (i == par) {
                continue;
            }
            self(self, i, cur);
            s.push_back(f[i]);
        }
        std::sort(s.rbegin(), s.rend());
        f[cur] = std::max(s[0] - 1, s[1]) + 1;
    };

    dfs(dfs, 0, -1);
    std::cout << f[0] << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
