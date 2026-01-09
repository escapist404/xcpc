#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    i64 m;

    std::cin >> n >> m;
    std::vector<int> w(n), l(n), r(n), d(n);
    {
        std::vector<std::tuple<int, int, int>> _(n);
        for (auto& [_w, _l, _r] : _) {
            std::cin >> _w >> _l >> _r;
        }
        std::sort(_.begin(), _.end(), std::greater<std::tuple<int, int, int>>());
        for (int i = 0; i < n; ++i) {
            std::tie(w[i], l[i], r[i]) = _[i];
            d[i] = r[i] - l[i];
        }
    }

    std::vector<i64> pre_d(n + 1), pre_dw(n + 1);
    for (int i = 0; i < n; ++i) {
        pre_d[i + 1] = pre_d[i] + d[i];
        pre_dw[i + 1] = pre_dw[i] + 1LL * d[i] * w[i];
    }

    i64 ans = 0;
    i64 sum_lw = std::inner_product(l.begin(), l.end(), w.begin(), 0LL, [](i64 x, i64 y) {
        return x + y;
    }, [](int x, int y) {
        return 1LL * x * y;
    });
    i64 sum_l = std::accumulate(l.begin(), l.end(), 0LL);

    for (int i = 0; i < n; ++i) {
        i64 now = sum_lw - 1LL * l[i] * w[i], res = m - sum_l + l[i];
        int j = std::lower_bound(pre_d.begin(), pre_d.begin() + i + 1, res) - pre_d.begin();
        now += pre_dw[j - 1];
        now += (res - pre_d[j - 1]) * w[j - 1];
        ans = std::max(ans, now);
    }

    std::cout << ans << "\n";

    return 0;
}
