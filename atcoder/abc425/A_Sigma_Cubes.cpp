#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    int ans = 0;
    for (int i = 1, sgn = -1; i <= n; ++i) {
        ans += sgn * i * i * i;
        sgn = -sgn;
    }

    std::cout << ans << "\n";
}