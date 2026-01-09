#include <bits/stdc++.h>

void solve() {
    int a, b, n;
    std::cin >> a >> b >> n;
    
    if (a >= 1LL * b * n || n == 1) {
        std::cout << 1 << "\n";
    } else if (a == b) {
        std::cout << 1 << "\n";
    } else {
        std::cout << 2 << "\n";
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
