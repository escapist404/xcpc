#include <bits/stdc++.h>

int main() {
    int n, q;
    std::cin >> n >> q;

    std::map<int, int> v;
    for (int i = 0; i < n; ++i) {
        v[i] = 1;
    }

    while (q--) {
        int x, y;
        std::cin >> x >> y;
        --y;
        int ans = 0;
        for (const auto& [c, i] : v) {
            if (c >= x) {
                break;
            } else {
                ans += i;
            }
        }
        v.erase(v.begin(), v.lower_bound(x));
        v[y] += ans;

        std::cout << ans << "\n";
    }

    return 0;
}