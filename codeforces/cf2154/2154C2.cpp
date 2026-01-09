#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    if (std::set<int>(a.begin(), a.end()).size() != n) {
        std::cout << 0 << "\n";
        return;
    }
    
    const int V = 2E5;
    std::vector<int> c(V + 1, 1E9);
    for (int i = 0; i < n; ++i) {
        c[a[i]] = b[i];
    }

    for (int d = 2; d <= V; ++d) {
        
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