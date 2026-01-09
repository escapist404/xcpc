#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long sum = std::accumulate(a.begin(), a.end(), 0LL);
    std::cout << std::min(sum - n + 1, (long long)n - std::count(a.begin(), a.end(), 0))  << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
