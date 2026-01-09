#include <bits/stdc++.h>

const int P = 998'244'353;

void solve();

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    std::vector<std::vector<int>> f(n, std::vector<int>(2));
    f[0][0] = f[0][1] = 1;

    for (int i = 1; i < n; ++i) {
        if (a[i] >= a[i - 1] && b[i] >= b[i - 1]) {
            (f[i][0] += f[i - 1][0]) %= P;
            (f[i][1] += f[i - 1][1]) %= P;
        }
        if (a[i] >= b[i - 1] && b[i] >= a[i - 1]) {
            (f[i][0] += f[i - 1][1]) %= P;
            (f[i][1] += f[i - 1][0]) %= P;
        }
    }

    std::cout << (f[n - 1][0] + f[n - 1][1]) % P << "\n";
}
