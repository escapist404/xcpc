#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> vis(n + 1);
    for (int x = 1; x * x < n; ++x) {
        for (int y = x + 1; x * x + y * y <= n; ++y) {
            vis[x * x + y * y]++;
        }
    }

    std::cout << std::count(vis.begin(), vis.end(), 1) << "\n";
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 1) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
    return 0;
}