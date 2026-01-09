#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (a.front() || a.back()) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}