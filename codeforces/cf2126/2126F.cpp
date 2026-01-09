#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using i64 = long long;

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, q;
            std::cin >> n >> q;
            std::vector<int> a(n);
            for (auto& i : a) {
                std::cin >> i;
                --i;
            }

            std::vector<std::vector<std::pair<int, i64>>> adj(n);
            std::vector<std::map<int, i64>> color(n);
            for (int i = 0; i < n - 1; ++i) {
                int u, v;
                i64 c;
                std::cin >> u >> v >> c;
                --u, --v;
                adj[u].emplace_back(v, c);
                adj[v].emplace_back(u, c);
            }

            std::vector<int> father(n);
            std::vector<i64> weight(n);

            i64 answer = 0;

            auto dfs = [&](auto& self, int current, int f) -> void {
                for (auto [v, c] : adj[current]) {
                    if (v == f) continue;
                    father[v] = current;
                    weight[v] = c;
                    color[current][a[v]] += c;
                    answer += c;
                    self(self, v, current);
                }
            };

            father[0] = -1;
            dfs(dfs, 0, -1);

            for (int i = 0; i < n; ++i) {
                if (color[i].count(a[i]))   answer -= color[i][a[i]];
            }

            for (int i = 0; i < q; ++i) {
                int v, x;
                std::cin >> v >> x;
                --v, --x;
                if (v != 0) {
                    color[father[v]][a[v]] -= weight[v];
                    color[father[v]][x] += weight[v];
                    if (a[v] == a[father[v]])   answer += weight[v];
                    if (x == a[father[v]]) answer -= weight[v];
                }
                answer += color[v][a[v]];
                answer -= color[v][x];

                a[v] = x;
                std::cout << answer << "\n";
            }
        }();
    }
}