#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        s[i + 1] = s[i] + a[i];
    }

    while (q--) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int x;
            std::cin >> x;
            --x;
            s[x + 1] = s[x] + s[x + 2] - s[x + 1];
        } else {
            int l, r;
            std::cin >> l >> r;

            --l;
            std::cout << s[r] - s[l] << "\n";
        }
    }

    return 0;
}
