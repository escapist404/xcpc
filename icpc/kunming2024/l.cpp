#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }
    for (int j = 0; j < m; ++j) {
        std::cin >> b[j];
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int boom = 0, cnt = n - std::count(a.begin(), a.end(), 0) + (a[0] == 0);
    int p = 0, q = 0;
    while (q < m) {
        while (p < n && boom >= a[p]) {
            ++p;
            ++boom;
        }
        if (q < m && cnt + boom >= b[q]) {
            cnt -= std::max(0, b[q] - boom);
            ++q;
            ++boom;
        } else {
            break;
        }
    }

    if (q == m) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
