#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> vis(n + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        vis[x]++;   
    }

    int mex = std::find(vis.begin(), vis.end(), 0) - vis.begin();
    std::cout << std::min(mex, k - 1) << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}