#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<std::vector<int>> adj(N);
            std::vector<int> count(N);

            for (int i = 0; i < N - 1; ++i) {
                int u, v;
                std::cin >> u >> v;
                --u, --v;
                adj[u].push_back(v);
                adj[v].push_back(u);
                ++count[u], ++count[v];
            }

            auto id = std::find(count.begin(), count.end(), 2) - count.begin();
            // for (int i = 0; i < N; ++i) {
            //     std::cerr << count[i] << " \n"[i == N - 1];
            // }
            if (id == N) {
                std::cout << "NO\n";
            } else {
                std::cout << "YES\n";
                auto dfs = [&](auto self, int current, int father, int depth) -> void {
                    if (depth & 1) {
                        std::cout << father + 1 << " " << current + 1 << "\n";
                    } else {
                        std::cout << current + 1 << " " << father + 1 << "\n";
                    }
                    for (const auto i : adj[current]) {
                        if (i == father) continue;
                        self(self, i, current, depth + 1);
                    }
                    return;
                };
                // std::cerr << id << std::endl;
                dfs(dfs, adj[id][0], id, 0);
                dfs(dfs, adj[id][1], id, 1);
            }
            return;
        }();
    }
}