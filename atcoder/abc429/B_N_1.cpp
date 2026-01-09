#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int sum = std::accumulate(a.begin(), a.end(), 0);
    for (int i = 0; i < n; ++i) {
        if (sum - a[i] == m) {
            std::cout << "Yes\n";
            return 0;
        }
    }

    std::cout << "No\n";

    return 0;
}