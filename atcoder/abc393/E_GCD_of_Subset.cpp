#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n, k;
    std::cin >> n >> k;

    const int V = 1000000;
    std::vector<std::vector<int>> map(V + 1);
    std::vector<int> count(V + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        map[x].push_back(i);
        count[x]++;
    }

    std::vector<int> ans(n);
    for (int d = V; d >= 1; --d) {
        int c = 0;
        for (int i = 1; i * d <= V; ++i) {
            c += count[i * d];
        }

        if (c >= k) {
            for (int i = 1; i * d <= V; ++i) {
                for (auto j : map[i * d]) {
                    ans[j] = d;
                }
                map[i * d].clear();
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}
