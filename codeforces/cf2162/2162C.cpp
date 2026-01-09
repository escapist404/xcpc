#include <bits/stdc++.h>

int highbit(int x) {
    int c = 0;

    while (x) {
        x >>= 1;
        c++;
    }

    return c;
}

void solve() {
    int a, b;
    std::cin >> a >> b;

    int n = highbit(a), m = highbit(b);
    if (m > n) {
        std::cout << -1 << "\n";
        return;
    }

    std::vector<int> ans;
    for (int i = 0; i < n; ++i) {
        bool f = (a >> i) & 1;
        bool g = (b >> i) & 1;
        if (f == g) {
            continue;
        } else {
            ans.push_back(1 << i);
        }
    }

    std::cout << ans.size() << "\n";
    for (int i = 0; i < (int)ans.size(); ++i) {
        std::cout << ans[i] << " \n"[i == (int)ans.size() - 1];
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