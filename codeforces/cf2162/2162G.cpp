#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    switch (n) {
        case 2:
            std::cout << "-1\n";
            break;
        case 3:
            std::cout << "1 3\n2 3\n";
            break;
        case 4:
            std::cout << "1 2\n1 3\n1 4\n";
            break;
        case 5:
            std::cout << "3 1\n1 4\n4 2\n2 5\n";
            break;
        default:
            std::vector<int> f(n + 1, 1);
            if (n % 2 == 1) {
                int u = (n - 1) / 2;
                int v = n - 4;
                f[v] = u + 1;
            } else {
                int u = n - 1;
                int v = (n - 4) / 2;
                f[u] = v + 1;
            }
            for (int i = 1; i <= n; ++i) {
                if (i == f[i]) {
                    continue;
                }
                std::cout << i << " " << f[i] << "\n";
            }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
