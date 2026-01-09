#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> father(N), size(N, 1);
    std::iota(father.begin(), father.end(), 0);
    auto get = [&](const auto& self, int u) -> int {
        return father[u] == u ? u : father[u] = self(self, father[u]);
    };
    auto merge = [&](int u, int v) {
        u = get(get, u), v = get(get, v);
        if (u == v) return;
        if (size[u] < size[v]) std::swap(u, v);
        father[v] = u, size[u] += size[v];
    };

    std::vector<bool> blocked(N);
    blocked[0] = true;
    int answer = 1;
    for (int i = 0; i < N; ++i) {
        answer -= blocked[i];
        blocked[i] = false;
        for (auto to : adj[i]) {
            if (to > i && blocked[to] == false) {
                answer++;
                blocked[to] = true;
            }
            if (to < i) {
                merge(to, i);
            }
        }
        if (size[get(get, 0)] == i + 1) {
            std::cout << answer << "\n";
        } else {
            std::cout << -1 << "\n";
        }
    }

    return 0;
}
