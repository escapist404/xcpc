#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int ans = 0;
    for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
            int s = std::accumulate(a.begin() + l, a.begin() + r, 0LL);
            bool ok = true;
            for (int i = l; i < r; ++i) {
                if (s % a[i] == 0) {
                    ok = false;
                }
            }
            if (ok) {
                ++ans;
            }
        }
    }

    std::cout << ans << "\n";
    return 0;
}
