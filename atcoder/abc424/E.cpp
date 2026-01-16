#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <iomanip>

void solve() {
    int n, k, x;
    std::cin >> n >> k >> x;
    --x;

    std::map<double, int> v;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        v[a]++;
    }

    while (k) {
        int d = std::min(k, v.rbegin()->second);
        k -= d;
        auto [val, cnt] = *v.rbegin();
        v[val / 2] += d * 2;
        v.erase(std::prev(v.end()));
        if (cnt != d) {
            v[val] = cnt - d;
        }
    }

    while (x) {
        int d = std::min(x, v.rbegin()->second);
        x -= d;
        if (d == v.rbegin()->second) {
            v.erase(std::prev(v.end()));
        }
    }

    std::cout << v.rbegin()->first << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(9);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
