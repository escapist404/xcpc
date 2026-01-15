#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <map>

using i64 = long long;
const int P = 998'244'353;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> to(n + 1);
    std::vector<std::map<int, std::vector<int>>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        std::cin >> x >> y;
        adj[to[x]][y].push_back(i);
        to[i] = adj[to[x]][y].front();
    }

    std::vector<int> ans;
    auto recursion = [&](auto& self, int x) -> void {
        for (auto [_, i] : adj[x]) {
            for (auto j : i) {
                ans.push_back(j);
            }
            self(self, i.front());
        }
    };

    recursion(recursion, 0);

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }

    return 0;
}
