#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i];
    }

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);

    std::sort(p.begin(), p.end(), [&](int x, int y) {
        return t[x] < t[y];
    });

    std::cout << p[0] + 1 << " " << p[1] + 1 << " " << p[2] + 1 << "\n";
    return 0;
}
