#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> c(n + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        c[x]++;
    }

    i64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += 1LL * c[i] * (c[i] - 1) * (n - c[i]) / 2;
    }

    std::cout << ans << "\n";
    return 0;
}