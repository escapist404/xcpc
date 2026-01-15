#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int a, b;
    std::cin >> a >> b;
    
    int ans = 0;
    {
        int ia = a, ib = b;
        int u = 0;
        while (ia >= (1 << u)) {
            ia -= 1 << u;
            u++;
            std::swap(ia, ib);
        }
        ans = std::max(ans, u);
    }
    {
        int ia = b, ib = a;
        int u = 0;
        while (ia >= (1 << u)) {
            ia -= 1 << u;
            u++;
            std::swap(ia, ib);
        }
        ans = std::max(ans, u);
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
