#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p(n), a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    a.erase(std::unique(a.begin(), a.end()), a.end());
    for (int i = n - 1; i >= 0; --i) {
        if (a.empty() == false && p[i] == a.back()) {
            a.pop_back();
        }
    }

    if (a.empty()) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
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