#include <bits/stdc++.h>

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> seg(q);
    for (auto& [l, r] : seg) {
        std::cin >> l >> r;
    }

    int idx = 0, count = 0;
    std::sort(seg.begin(), seg.end());
    for (auto [l, r] : seg) {
        if (l > idx) {
            idx = r;
            ++count;
        } else {
            idx = std::min(idx, r);
        }
    }

    std::cout << std::__lg(count) + 1 << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
