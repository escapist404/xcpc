#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>
#include <set>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> adj(n * k);
    for (int i = 0; i < n * k; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> par(n * k), size(n * k, 1);
    auto find_par = [&](auto& self, int cur, int last) -> void {
        par[cur] = last;
        for (const auto next : adj[cur]) {
            if (next == last) {
                continue;
            }
            self(self, next, cur);
        }
    };

    find_par(find_par, 0, -1);

    std::queue<int> queue;
    for (int i = 0; i < n * k; ++i) {
        if (adj[i].size() == 1) {
            queue.push(i);
        }
    }

    std::vector<std::set<int>> res(n * k);
    while (queue.size()) {
        auto cur = queue.front();
        queue.pop();
        int dep = size[cur];
        while (cur != -1 && dep < k && adj[cur].size() != 2) {
            cur = par[cur];
            ++dep;
        }
        if (res[cur])
    }
}
