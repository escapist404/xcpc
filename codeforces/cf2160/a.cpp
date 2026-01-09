#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::set<int> a;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        a.insert(x);
    }

    for (int i = 0; i < n + 1; ++i) {
        if (a.count(i) == 0) {
            std::cout << i << "\n";
            return;
        }
    }
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}