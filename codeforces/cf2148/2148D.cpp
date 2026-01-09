#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    using i64 = long long;
    i64 ans = 0;
    std::vector<int> odd;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (a % 2 == 0) {
            ans += a;
        } else {
            odd.push_back(a);
        }
    }

    std::sort(odd.begin(), odd.end(), std::greater<int>());
    for (int i = 0; i < (int)odd.size() / 2 + odd.size() % 2; ++i) {
        ans += odd[i];
    }

    std::cout << (1 - odd.empty()) * ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}