#include <bits/stdc++.h>

void solve() {
    int mu, sigma, n;
    std::cin >> mu >> sigma >> n;

    int z = 100 * (n - mu) / sigma;

    std::cout << z / 10 + 1 << " " << z % 10 + 1 << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}