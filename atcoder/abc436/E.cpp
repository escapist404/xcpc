#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <deque>

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
        --p[i];
    }

    i64 ans = 0;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        int c = 0, x = i;
        while (v[x] == 0) {
            v[x] = 1;
            x = p[x];
            c++;
        }
        ans += 1LL * c * (c - 1) / 2;
    }

    std::cout << ans << "\n";
    return 0;
}
