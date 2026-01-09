#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

int main() {
    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> father(N);
    std::iota(father.begin(), father.end(), 0);
    std::vector<std::set<int>> set(N);

    auto get = [&](const auto& self, const int u) -> int {
        return u == father[u] ? u : father[u] = self(self, father[u]);
    };

    auto merge = [&](int u, int v) {
        u = get(get, u), v = get(get, v);
        if (u == v) return;
        if (set[u].size() < set[v].size()) {
            std::swap(u, v);
        }

        father[v] = u;
        for (const auto i : set[v]) {
            set[u].insert(i);
        }
    };

    while (Q--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int u, v;
            std::cin >> u >> v;
            --u, --v;
            merge(u, v);
        } else if (type == 2) {
            int v;
            std::cin >> v;
            --v;
            int f = get(get, v);
            if (set[f].count(v)) {
                set[f].erase(set[f].lower_bound(v));
            } else {
                set[f].insert(v);
            }
        } else {
            int v;
            std::cin >> v;
            --v;
            int f = get(get, v);
            if (set[f].size()) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
}
