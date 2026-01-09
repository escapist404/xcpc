#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    int tt;
    std::cin >> tt;

    std::vector<int> f(500001);
    f[1] = 1;
    for (int i = 3; i <= 500000; i += 2) {
        f[i] = (i + 1) / 2;
        for (int j = 3; j * j <= i; j += 2) {
            if (i % j != 0) continue;
            int u = j - 2, v = i / j - 2;
            if (v & 1) f[i] = std::min(f[i], f[u] + f[v] + 1);
        }
    }

    while (tt--) {
        [&]() {
            int N;
            std::cin >> N;
            if (N % 2 == 0) std::cout << -1 << "\n";
            else std::cout << f[N] << "\n";
        }();
    }
}