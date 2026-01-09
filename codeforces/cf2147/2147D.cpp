#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    std::map<int, int> c;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        c[x]++;
    }

    using i64 = long long;
    i64 a = 0, b = 0;
    int t = 0;
    for (const auto& [u, v] : c) {
        if (t == 0) {
            a += v * ((u + 1) / 2);
            b += v * (u / 2);
        } else {
            a += v * (u / 2);
            b += v * ((u + 1) / 2);
        }
        t ^= u & 1;
    }

    std::cout << a << " " << b << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}