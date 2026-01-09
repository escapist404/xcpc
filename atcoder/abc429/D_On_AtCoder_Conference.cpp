#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n, c;
    i64 m;
    std::cin >> n >> m >> c;

    std::vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        a.push_back(a[i] + m);
    }

    i64 ans = 0;
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        while (pos < 2 * n && a[i + c] >= a[pos]) {
            ++pos;
        }
        ans += (a[i + 1] - a[i]) * (pos - i - 1);
    }

    std::cout << ans << "\n";
    return 0;
}