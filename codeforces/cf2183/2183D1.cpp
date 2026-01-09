#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> father(n);
    father[0] = -1;
    auto recursion = [&](auto& self, int x) -> void {
        for (auto i : adj[x]) {
            if (i == father[x]) {
                continue;
            }
            father[i] = x;
            self(self, i);
        }
    };

    recursion(recursion, 0);

    int ans = 1, last = 1, cur = 1;
    std::vector<int> set = adj[0];
    while (set.size()) {
        cur = set.size();
        if (last == 1) {
            ans = std::max(ans, cur + 1);
        } else {
            ans = std::max(ans, cur);
        }
        std::vector<int> next;
        last = 0;
        for (auto i : set) {
            bool ok = false;
            for (auto j : adj[i]) {
                if (father[i] == j) {
                    continue;
                }
                next.push_back(j);
                ok = true;
            }
            last += ok;
        }
        set = next;
    }

    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}