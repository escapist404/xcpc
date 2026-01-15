#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> d(n);
    i64 s = 0;
    for (int i = 0; i < n; ++i) {
        int w, p;
        std::cin >> w >> p;
        s += p;
        d[i] = w + p;
    }

    std::sort(d.begin(), d.end());
    int p = 0;
    while (p < n) {
        if (s >= d[p]) {
            s -= d[p++];
        } else {
            break;
        }
    }

    std::cout << p << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
