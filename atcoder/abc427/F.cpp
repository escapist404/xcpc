#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto find_comb = [m](const std::vector<int>& b) {
        std::vector<int> in = {}, ex = {0};
        for (const auto v : b) {
            for (auto& x : ex) {
                in.push_back(x);
                (x += v) %= m;
            }
            std::swap(in, ex);
        }
        std::sort(in.begin(), in.end());
        std::sort(ex.begin(), ex.end());
        return std::make_pair(in, ex);
    };

    auto lo = std::vector<int>(a.begin(), a.begin() + n / 2);
    auto hi = std::vector<int>(a.rbegin(), a.rend() - n / 2);

    auto [lo_in, lo_ex] = find_comb(lo);
    auto [hi_in, hi_ex] = find_comb(hi);

    i64 ans = 0;
    for (auto i : lo_in) {
        int j = (m - i) % m;
        ans += std::upper_bound(hi_ex.begin(), hi_ex.end(), j) - std::lower_bound(hi_ex.begin(), hi_ex.end(), j);
    }
    for (auto i : hi_in) {
        int j = (m - i) % m;
        ans += std::upper_bound(lo_ex.begin(), lo_ex.end(), j) - std::lower_bound(lo_ex.begin(), lo_ex.end(), j);
    }
    for (auto i : hi_ex) {
        int j = (m - i) % m;
        ans += std::upper_bound(lo_ex.begin(), lo_ex.end(), j) - std::lower_bound(lo_ex.begin(), lo_ex.end(), j);
    }

    std::cout << ans << "\n";
    return 0;
}
