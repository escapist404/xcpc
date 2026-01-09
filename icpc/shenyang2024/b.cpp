#include <bits/stdc++.h>

int main() {
    int n, m;

    std::cin >> n >> m;
    std::vector<int> a(n), b(m);

    auto dfs = [&](auto& self, int x) -> void {
        if (x == n + m) {
            std::set<int> s;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    s.insert(a[i] * b[j] % (n * m));
                }
            }
            if (s.size() == n * m) {
                std::cout << "YES\n";
                for (int i = 0; i < n; ++i) {
                    std::cout << a[i] << " \n"[i == n - 1];
                }
                for (int j = 0; j < m; ++j) {
                    std::cout << b[j] << " \n"[j == m - 1];
                }
                exit(0);
            }
        } else if (x >= n) {
            int y = x - n;
            for (b[y] = y; b[y] < n * m; b[y] += m) {
                self(self, x + 1);
            }
        } else {
            for (a[x] = x; a[x] < n * m; a[x] += n) {
                self(self, x + 1);
            }
        }
    };

    dfs(dfs, 0);
    std::cout << "NO\n";
    return 0;
}