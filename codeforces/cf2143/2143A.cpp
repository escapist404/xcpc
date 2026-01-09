#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::deque<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        if (a.front() == i) {
            a.pop_front();
        } else if (a.back() == i) {
            a.pop_back();
        } else {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}