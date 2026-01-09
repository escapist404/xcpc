#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> c;
    for (int i = 1; i <= n; ++i) {
        c.push_back(std::count(a.begin(), a.end(), i));
        if (c.back() == 0) {
            c.pop_back();
        }
    }

    int ans = 0;
    std::sort(c.begin(), c.end());
    for (int i = 0; i < (int)c.size(); ++i) {
        ans = std::max((int)(c.size() - i) * c[i], ans);
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}