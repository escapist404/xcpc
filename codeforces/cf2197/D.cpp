#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    const int B = ceil(sqrt(n / log(n)));
    std::vector<std::vector<int>> o(B);

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int v = 1; v < B; ++v) {
            if (1LL * v * a[i] >= n) {
                break;
            }
            int j = i - v * a[i];
            auto it = std::lower_bound(o[v].begin(), o[v].end(), j);
            if (it != o[v].end() && *it == j) {
                ans++;
            }
        }
        if (a[i] >= B) {
            for (int v = 1; i + v * a[i] < n; ++v) {
                int j = i + v * a[i];
                if (a[j] == v) {
                    ans++;
                }
            }
        } else {
            o[a[i]].push_back(i);
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
