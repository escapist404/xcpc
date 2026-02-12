#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, m;
    i64 h;
    std::cin >> n >> m >> h;

    std::vector<int> p(m), f(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> p[i] >> f[i];
        --p[i];
    }

    auto find_max = [&](int t) {
        std::vector<i64> dd(n + 2);
        for (int i = 0; i < t; ++i) {
            int lp = std::max(p[i] - f[i] + 1, 0);
            int rp = std::min(p[i] + f[i] - 1, n - 1);
            i64 v = f[i] - (p[i] - lp);
            dd[lp] += v;
            dd[lp + 1] -= v - 1;
            dd[p[i] + 1] += -2;
            dd[rp + 2] += 1;
        }

        std::vector<i64> d(n + 1);
        d[0] = dd[0];
        for (int i = 1; i <= n; ++i) {
            d[i] = d[i - 1] + dd[i];
        }

        std::vector<i64> a(n);
        a[0] = d[0];
        for (int i = 1; i < n; ++i) {
            a[i] = a[i - 1] + d[i];
        }

        return *std::max_element(a.begin(), a.end());
    };

    if (find_max(m) > h) {
        int l = 0, r = m;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (find_max(mid) <= h) {
                l = mid;
            } else {
                r = mid;
            }
        }
        std::cout << "Yes\n" << r << "\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
