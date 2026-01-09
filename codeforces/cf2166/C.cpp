#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    
    std::set<std::tuple<int, int, int>> min;
    for (int i = 0; i < n; ++i) {
        min.emplace(std::max(a[i], a[(i + 1) % n]), i, (i + 1) % n);
    }
    
    std::vector<int> prev(n), next(n);
    for (int i = 0; i < n; ++i) {
        next[i] = (i + 1) % n;
        prev[(i + 1) % n] = i;
    }
        
    i64 ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        auto [v, l, r] = *min.begin();
        ans += v;
        min.erase(min.begin());
        
        int v1 = std::max(a[prev[l]], a[l]);
        int v2 = std::max(a[r], a[next[r]]);
        min.erase({v1, prev[l], l});
        min.erase({v2, r, next[r]});
        
        a[l] = v;
        min.emplace(std::max(v1, v), prev[l], l);
        min.emplace(std::max(v2, v), l, next[r]);
        
        next[l] = next[r];
        prev[next[r]] = l;
    }
    
    std::cout << ans << "\n";
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
