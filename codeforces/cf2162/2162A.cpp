#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cout << *std::max_element(a.begin(), a.end()) << "\n";
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}