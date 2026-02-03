#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> r[i];
        --r[i];
    }

    std::set<int> s;
    std::vector<std::vector<int>> c(n);
    for (int i = 0; i < n; ++i) {
        c[r[i]].push_back(i);
    }

    i64 ans = 0;
    std::vector<int> a(n);
    for (int v = 0; v < n; ++v) {
        for (auto i : c[v]) {
            auto it = s.lower_bound(i);
            int chg = v;
            if (it != s.end()) {
                chg = std::min(a[*it] + *it - i, chg);
            }
            if (it != s.begin()) {
                --it;
                chg = std::min(a[*it] + i - *it, chg);
            }
            a[i] = chg;
            ans += v - chg;
            s.insert(i);
        }
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
