#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int par;
        std::cin >> par;
        --par;
        adj[par].push_back(i);
    }
    
    int m = n - 1;
    std::vector<int> s;
    auto dfs = [&](auto& self, int cur, int dep) -> void {
        if (s.size() <= dep) {
            s.push_back(0);
        }
        s[dep]++;

        if (adj[cur].size() == 0) {
            m = std::min(m, dep);
        }
        for (auto to : adj[cur]) {
            self(self, to, dep + 1);
        }
    };

    dfs(dfs, 0, 0);
    
    ++m;
    int r = 0;
    std::bitset<200001> f;
    f[0] = true;
    
    for (int i = 0; i < m; ++i) {
        f |= (f << s[i]);
        r += s[i];
    }

    for (int i = 0; i < n - r; ++i) {
        f |= (f << 1);
    }

    if (f[k] == true) {
        std::cout << m << "\n";
    } else {
        std::cout << m - 1 << "\n";
    }
}

int main() {
    int tc;
    std::cin >> tc;
    while (tc--) {
        solve();
    }

    return 0;
}
