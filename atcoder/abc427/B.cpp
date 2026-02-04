#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    a[0] = 1;

    auto root = [](int x) {
        int s = 0;
        while (x) {
            s += x % 10;
            x /= 10;
        }
        return s;
    };

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            a[i] += root(a[j]);
        }
    }

    std::cout << a[n] << "\n";
    return 0;
}
