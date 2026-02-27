#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto v = a;
    std::sort(v.begin(), v.end());
    for (auto& i : a) {
        i = std::lower_bound(v.begin(), v.end(), i) - v.begin();
    }

    int m = v.size();
    std::vector<std::vector<int>> l(m);
    for (int i = 0; i < n; ++i) {
        l[a[i]].push_back(i);
    }

    i64 ans = 0, cur = 0;
    for (int i = 0; i < m; ++i) {
        if (l[i].empty() == false) {
            cur += l[i].back() + 1;
        }
    }

    for (int r = n - 1; r >= 0; --r) {
        ans += cur * (n - r);
        cur -= l[a[r]].back() + 1;
        l[a[r]].pop_back();
        if (l[a[r]].empty() == false) {
            cur += l[a[r]].back() + 1;
        }
    }

    std::cout << ans << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
