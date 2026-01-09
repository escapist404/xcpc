#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);

    a[0] = n;
    a[1] = 1;
    int c = 1 + (m - 1) * n;
    for (int i = 2; i < n; ++i) {
        a[i] = a[i - 1] + c;
        a[i] %= n * m;
    }

    b[0] = m;
    b[1] = 1;
    c = 1 + (n - 1) * m;
    for (int i = 2; i < m; ++i) {
        b[i] = b[i - 1] + c;
        b[i] %= n * m;
    }

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
    } else {
        std::cout << "NO\n";
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