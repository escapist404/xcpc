#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>

using i64 = long long;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        deg[i] = adj[i].size();
    }

    int k = *std::max_element(deg.begin(), deg.end()) + 1;
    std::vector<std::vector<int>> type(k);
    for (int i = 0; i < n; ++i) {
        type[deg[i]].push_back(i);
    }

    std::vector<int> dis(n, 1E9);
    for (int v = k - 1; v >= 0; --v) {
        std::queue<int> queue;
        for (auto x : type[v]) {
            queue.emplace(x);
        }
        while (queue.empty() == false) {
            auto x = queue.front();
            queue.pop();
            for (auto y : adj[x]) {
                if (deg[y] <= v && dis[y] > dis[x] + 1) {
                    dis[y] = dis[x] + 1;
                    queue.push(y);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << (dis[i] == 1E9 ? -1 : dis[i]) << " \n"[i == n - 1];
    }

    return 0;
}
