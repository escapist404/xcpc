#include <bits/stdc++.h>

int main() {
    int T, M;
    std::cin >> T >> M;

    std::vector<std::vector<int>> comb(5001, std::vector<int>(5001));
    for (int i = 0; i <= 5000; ++i) {
        comb[i][0] = 1 % M;
        for (int j = 1; j < i; ++j) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % M;
        }
        comb[i][i] = 1 % M;
    }
    
    while (T--) {
        int n;
        std::cin >> n;
        std::vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> c[i];
        }

        int s = std::accumulate(c.begin(), c.end(), 0);
        int ans = 1 % M;
        for (int i = 0; i < n; ++i) {
            ans = 1LL * ans * comb[s][c[i]] % M;
            s -= c[i];
        }

        std::cout << ans << "\n";
    }
}