#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k, l, r;
    std::cin >> n >> k >> l >> r;
    ++r;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::map<int, int> c[2];
    int s[] = {0, 0}, d[] = {0, 0};

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        while (s[0] < n && d[0] < k) {
            if (c[0][a[s[0]]] == 0) {
                d[0]++;
            }
            c[0][a[s[0]]]++;
            s[0]++;
        }
        while (s[1] < n && d[1] <= k) {
            if (c[1][a[s[1]]] == 0) {
                d[1]++;
            }
            c[1][a[s[1]]]++;
            s[1]++;
        }

        if (d[0] < k) {
            break;
        }

        if (d[0] == k && d[1] == k + 1) {
            ans += std::max(std::min(s[1], i + r) - std::max(s[0], i + l), 0);
        } else {
            ans += std::max(std::min(n + 1, i + r) - std::max(s[0], i + l), 0);
        }

        c[0][a[i]]--;
        if (c[0][a[i]] == 0) {
            d[0]--;
        }
        c[1][a[i]]--;
        if (c[1][a[i]] == 0) {
            d[1]--;
        }
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}