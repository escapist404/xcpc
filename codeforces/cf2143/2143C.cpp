#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, x, y;
        std::cin >> u >> v >> x >> y;
        --u, --v;
        if (x > y) {
            adj[u].push_back(v);
        } else {
            adj[v].push_back(u);
        }
    }

    std::vector<int> ans(n), in(n);
    std::queue<int> queue;
    for (int i = 0; i < n; ++i) {
        for (auto to : adj[i]) {
            in[to]++;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (in[i] == 0) {
            queue.push(i);
        }
    }

    int val = n;
    while (queue.size()) {
        int cur = queue.front();
        queue.pop();
        ans[cur] = val--;
        for (auto to : adj[cur]) {
            in[to]--;
            if (in[to] == 0) {
                queue.push(to);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}