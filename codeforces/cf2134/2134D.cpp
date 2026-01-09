#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<std::vector<int>> adj(N);

            for (int i = 0; i < N - 1; ++i) {
                int u, v;
                std::cin >> u >> v;
                --u, --v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            std::vector<int> dis(N), father(N);

            auto dfs = [&](const auto& self, int current, int fa) -> void {
                father[current] = fa;
                for (auto to : adj[current]) {
                    if (to == fa) continue;
                    dis[to] = dis[current] + 1;
                    self(self, to, current);
                }
            };

            dfs(dfs, 0, -1);
            int u = std::max_element(dis.begin(), dis.end()) - dis.begin();
            dis = std::vector<int>(N);
            dfs(dfs, u, -1);
            int v = std::max_element(dis.begin(), dis.end()) - dis.begin();
            
            std::vector<int> diameter;
            int current = v;
            while (current != -1) {
                diameter.push_back(current);
                current = father[current];
            }

            int C = diameter.size();
            for (int i = 1; i < C - 1; ++i) {
                if (adj[diameter[i]].size() > 2) {
                    int index = 0;
                    while (adj[diameter[i]][index] == diameter[i - 1] || adj[diameter[i]][index] == diameter[i + 1]) {
                        ++index;
                    }
                    std::cout << diameter[i - 1] + 1 << " " << diameter[i] + 1 << " " << adj[diameter[i]][index] + 1 << "\n";
                    return;
                }
            }

            std::cout << -1 << "\n";
        }();
    }

    return 0;
}
