#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int n, m, x, y;
    std::cin >> n >> m >> x >> y;
    --x, --y;

    bool ok = true;
    std::vector<std::pair<int, int>> e(m);
    for (auto& [u, v] : e) {
        std::cin >> u >> v;
        --u, --v;
        if (u == x && v == y || u == y && v == x) {
            ok = false;
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
