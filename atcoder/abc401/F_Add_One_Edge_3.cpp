#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int N[2], dia[2];
    std::vector<std::vector<int>> adj[2];
    std::vector<int> depth[2], far[2];

    for (int type = 0; type < 2; ++type) {
        std::cin >> N[type];
        adj[type].resize(N[type]);

        for (int i = 0; i < N[type] - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
            --u, --v;
            adj[type][u].push_back(v);
            adj[type][v].push_back(u);
        }

        auto dfs = [type, &adj, &depth](const auto& self, int current, int father) -> void {
            for (const auto to : adj[type][current]) {
                if (to == father) continue;
                depth[type][to] = depth[type][current] + 1;
                self(self, to, current);
            }
        };

        depth[type] = std::vector(N[type], 0);
        dfs(dfs, 0, -1);
        int u = std::max_element(depth[type].begin(), depth[type].end()) - depth[type].begin();
        depth[type] = std::vector(N[type], 0);
        dfs(dfs, u, -1);
        far[type] = depth[type];        
        int v = std::max_element(depth[type].begin(), depth[type].end()) - depth[type].begin();
        depth[type] = std::vector(N[type], 0);
        dia[type] = far[type][v];
        dfs(dfs, v, -1);

        for (int i = 0; i < N[type]; ++i) {
            far[type][i] = std::max(far[type][i], depth[type][i]);
        }
    }
    
    std::sort(far[0].begin(), far[0].end(), std::greater<int>());
    std::sort(far[1].begin(), far[1].end());
    
    using i64 = long long;
    i64 sum = std::accumulate(far[1].begin(), far[1].end(), 0LL), answer = 0;
    int iter = 0;
    for (int i = 0; i < N[0]; ++i) {
        while (iter < N[1] && far[0][i] + far[1][iter] + 1 <= std::max(dia[0], dia[1])) {
            sum -= far[1][iter];
            ++iter;
        }
        answer += sum + 1LL * iter * std::max(dia[0], dia[1]) + 1LL * (N[1] - iter) * (far[0][i] + 1);
    }

    std::cout << answer << "\n";
}
