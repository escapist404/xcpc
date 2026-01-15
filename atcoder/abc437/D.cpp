#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using i64 = long long;
const int P = 998'244'353;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    std::sort(b.begin(), b.end());

    std::vector<i64> s(m + 1);
    for (int i = 0; i < m; ++i) {
        s[i + 1] = s[i] + b[i];
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        int idx = std::upper_bound(b.begin(), b.end(), a[i]) - b.begin();
        i64 u = 1LL * idx * a[i] - s[idx];
        i64 v = s[m] - s[idx] - 1LL * (m - idx) * a[i];
        (ans += u + v) %= P;
    }

    std::cout << ans << "\n";

    return 0;
}
