#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto& i : a) {
        std::cin >> i;
    }

    int s = 0, b = 4 * n / 5 + ((4 * n) % 5 > 0);
    for (int i = 0; i < n; ++i) {
        int c = std::count_if(a.begin(), a.end(), [&](int x) {
            return x <= a[i];
        }) - 1;
        if (c >= b) {
            s += a[i];
        }
    }

    std::cout << s << "\n";

    return 0;
}
