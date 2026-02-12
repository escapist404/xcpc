#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <utility>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, p;
    std::cin >> n >> p;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::tuple<int, int, int> ans = {-1, 0, 0};
    auto find = [&](auto& self, int l, int r) -> void {
        if (l + 1 == r) {
            ans = std::max(ans, std::make_tuple(a[l], l, l));
            return;
        }
        int m = l + (r - l) / 2;
        self(self, l, m);
        self(self, m, r);
        std::vector<std::pair<int, int>> b(r - m);
        for (int i = m, s = 0; i < r; ++i) {
            (s += a[i]) %= p;
            b[i - m] = {s, i};
        }
        std::sort(b.begin(), b.end());
        for (int i = m - 1, s = 0; i >= l; --i) {
            (s += a[i]) %= p;
            auto it = std::lower_bound(b.begin(), b.end(), std::make_pair(p - s, 0));
            if (it != b.begin()) {
                --it;
                ans = std::max(ans, std::make_tuple(s + it->first, i, it->second));
            }
        }
    };

    find(find, 0, n);
    std::cout << std::get<1>(ans) << " " << std::get<2>(ans) << " " << std::get<0>(ans) << "\n";
    return 0;
}
