#include <bits/stdc++.h>

void solve() {
    int n, m, k, w;
    std::cin >> n >> m >> k >> w;
    
    std::vector<int> a(n), b(m);
    std::for_each(a.begin(), a.end(), [](auto& v) {
        std::cin >> v;
        --v;
    });
    std::for_each(b.begin(), b.end(), [](auto& v) {
        std::cin >> v;
        --v;
    });

    auto solve_single = [](std::vector<int> x) {
        int n = x.size();
        std::vector<int> f(n + 1);
        f[0] = 0;
        for (int i = 0; i < n; ++i) {
            
        }
    };
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