#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::map<int, int> pre, suf;
    for (int i = 0; i < n; ++i) {
        suf[a[i]]++;
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        suf[a[i]]--;
        if (a[i] % 5 == 0) {
            int b = a[i] / 5;
            ans += 1LL * pre[3 * b] * pre[7 * b];
            ans += 1LL * suf[3 * b] * suf[7 * b];
        }
        pre[a[i]]++;
    }

    std::cout << ans << "\n";
    return 0;
}