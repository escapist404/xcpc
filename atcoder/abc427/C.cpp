#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> e(m);
    for (auto& [u, v] : e) {
        std::cin >> u >> v;
        --u, --v;
    }

    int ans = m;
    for (int S = 0; S < 1 << n; ++S) {
        int cut = 0;
        for (const auto [u, v] : e) {
            if ((S >> u & 1) == (S >> v & 1)) {
                ++cut;
            }
        }
        ans = std::min(cut, ans);
    }

    std::cout << ans << "\n";
    return 0;
}
