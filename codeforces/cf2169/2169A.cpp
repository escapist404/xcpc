#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, a;
    std::cin >> n >> a;

    int lt = 0, gt = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (x < a) {
            lt++;
        } else if (x > a) {
            gt++;
        }
    }

    if (lt > gt) {
        std::cout << a - 1 << "\n";
    } else {
        std::cout << a + 1 << "\n";
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
