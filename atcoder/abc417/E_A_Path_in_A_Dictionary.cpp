#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, M, X, Y;
            std::cin >> N >> M >> X >> Y;

            --X, --Y;
            std::vector<std::vector<int>> adj(N);
            for (int i = 0; i < M; ++i) {
                int u, v;
                std::cin >> u >> v;
                --u, --v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            for (auto& i : adj) {
                std::sort(i.begin(), i.end());
            }

            std::vector<bool> visited(N);
            std::vector<int> stack;
            bool ok = false;

            auto dfs = [&](auto self, int current) -> void {
                visited[current] = true;
                stack.push_back(current);

                if (current == Y) {
                    ok = true;
                    return;
                }

                for (auto i : adj[current]) {
                    if (ok == true) {
                        return;
                    }
                    if (visited[i] == false) {
                        self(self, i);
                    }
                }

                if (ok == true) {
                    return;
                }

                stack.pop_back();
            };

            dfs(dfs, X);
            for (auto i : stack) {
                std::cout << i + 1 << " ";
            }
            std::cout << "\n";
        }();
    }
}