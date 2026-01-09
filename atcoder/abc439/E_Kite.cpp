#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n), p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i];
        p[i] = i;
    }

    std::sort(p.begin(), p.end(), [&a, &b](int x, int y) {
        if (a[x] != a[y]) {
            return a[x] < a[y];
        }
        return b[x] > b[y];
    });

    std::vector<int> f;
    for (int i = 0; i < n; ++i) {
        auto lft = std::lower_bound(f.begin(), f.end(), b[p[i]]);
        if (lft == f.end()) {
            f.push_back(b[p[i]]);
        } else {
            *lft = b[p[i]];
        }
    }

    std::cout << f.size() << "\n";
    return 0;
}
