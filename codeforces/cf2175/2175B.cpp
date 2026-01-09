#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, l, r;
    std::cin >> n >> l >> r;
    --l;

    std::vector<int> a(n);
    std::mt19937 rnd(time(0));
    int c = 0;
    for (int i = 0; i < r - 1; ++i) {
        a[i] = (i + 1) ^ c;
        c ^= a[i];
    }
    a[r - 1] = c ^ l;
    c ^= a[r - 1];
    for (int i = r; i < n; ++i) {
        a[i] = (i + 1) ^ c;
        c ^= a[i];
    }

    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " \n"[i == n - 1];
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