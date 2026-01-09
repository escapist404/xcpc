#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_set>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, M, V;
            std::cin >> N >> M >> V;

            std::vector<int> weight(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> weight[i];
            }

            std::vector<std::vector<int>> adj(N);
            std::vector<std::pair<int, int>> edge(M);
            for (auto& [u, v] : edge) {
                std::cin >> u >> v;
                --u, --v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            std::vector<int> id(N, -1), low(N);
            std::vector<std::unordered_set<int>> bridge(N);
            auto find_bridge = [&, i = 0](auto& self, int current, int father) mutable -> void {
                low[current] = id[current] = i++;
                for (const auto to : adj[current]) {
                    if (id[to] == -1) {
                        self(self, to, current);
                        low[current] = std::min(low[current], low[to]);
                        if (low[to] > id[current]) {
                            bridge[current].insert(to);
                            bridge[to].insert(current);
                        }
                    } else if (to != father) {
                        low[current] = std::min(low[current], id[to]);
                    }
                }
            };

            find_bridge(find_bridge, 0, -1);

            std::vector<int> color(N, -1);
            bool odd_cycle = false, different_weight = false;
            int base_weight = -1;

            auto find_component = [&](auto& self, int current, int father, int current_color) -> void {
                color[current] = current_color;

                if (base_weight == -1) {
                    base_weight = weight[current];
                }
                if (weight[current] != -1 && base_weight != weight[current]) {
                    different_weight = true;
                }

                for (const auto to : adj[current]) {
                    if (to != father && bridge[current].count(to) == 0) {
                        if (color[to] == -1) {
                            self(self, to, current, current_color ^ 1);
                        }
                        if (color[to] == current_color) {
                            odd_cycle = true;
                        }
                    }
                }
            };

            int answer = 1;
            const int P = 998'244'353;

            for (int i = 0; i < N; ++i) {
                odd_cycle = different_weight = false;
                base_weight = -1;

                if (color[i] == -1) {
                    find_component(find_component, i, -1, 0);
                    if (different_weight) {
                        answer = 0;
                    }
                    if (odd_cycle) {
                        if (base_weight > 0) {
                            answer = 0;
                        }
                    } else {
                        if (base_weight == -1) {
                            answer = 1LL * answer * V % P;
                        }
                    }
                }
            }

            std::cout << answer << "\n";
        }();
    }
}