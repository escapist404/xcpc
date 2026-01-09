#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

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

            int ans = 0;
            std::vector<int> carry(N);
            for (int i = 0; i < N; ++i) {
                if (adj[i].size() == 1) {
                    ++ans;
                    ++carry[adj[i][0]];
                    ++carry[i];
                }
            }

            std::cout << ans - *std::max_element(carry.begin(), carry.end()) << "\n";
        }();
    }
}