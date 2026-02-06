#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using i64 = long long;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    int t, s, c;
    std::cin >> t >> s >> c;
    --t, --s;

    for (int i = 1; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
    }

    std::vector<i64> dis(n, 1E18);
    dis[s] = 0;
    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<std::pair<i64, int>>> queue;
    queue.emplace(0, s);
    while (queue.empty() == false) {
        auto [d, x] = queue.top();
        queue.pop();
        if (dis[x] < d) {
            continue;
        }
        for (auto [i, w] : adj[x]) {
            if (dis[i] > dis[x] + w) {
                dis[i] = dis[x] + w;
                queue.emplace(d + w, i);
            }
        }
    }

    std::cout << ((dis[t] == 1E18) ? (-1) : (dis[t] + c)) << "\n";
}
