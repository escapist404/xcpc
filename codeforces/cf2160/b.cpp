#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    i64 last = 0;
    int c = 0;
    for (int i = 0; i < n; ++i) {
        i64 now;
        std::cin >> now;
        if (now - last == i + 1) {
            a[i] = ++c;
        } else {
            a[i] = a[i - now + last];
        }
        last = now;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " \n"[i == n - 1];
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