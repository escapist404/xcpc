#include <bits/stdc++.h>

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;

    if (s.find('B') != std::string::npos) {
        while (q--) {
            int x;
            std::cin >> x;
            int p = 0, ans = 0;
            while (x) {
                if (s[p] == 'A') {
                    x--;
                } else {
                    x >>= 1;
                }
                p++;
                ans++;
                if (p == n) {
                    p = 0;
                }
            }
            std::cout << ans << "\n";
        }
    } else {
        while (q--) {
            int x;
            std::cin >> x;
            std::cout << x << "\n";
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}