#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(1 << n);
    for (int i = 0; i < 1 << n; ++i) {
        std::cin >> a[i];
    }

    auto compute = [&](auto& compute, int x, int p) -> std::vector<int> {
        if (x == n) {
            return {a[p]};
        }
        auto f = compute(compute, x + 1, p);
        auto g = compute(compute, x + 1, p ^ (1 << x));
        
        std::vector<int> h(f);
        for (int i = 0; i < (int)f.size(); ++i) {
            h[i] += g[i];
        }
        
        f.insert(f.end(), g.begin(), g.end());
        f.insert(f.end(), h.begin(), h.end());
        return f;
    };

    auto f = compute(compute, 0, 0);
    std::cout << std::accumulate(f.begin(), f.end(), 0, [](int x, int y) { return x ^ y; }) << "\n";
    return 0;
}
