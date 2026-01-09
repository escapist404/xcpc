#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());
    int max = 0;
    for (int i = 0; i < n; i += 2) {
        max = std::max(max, a[i + 1] - a[i]);
    }

    std::cout << max << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}