#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        int ans = -1;
        for (int j = 0; j < i; ++j) {
            if (a[j] > a[i]) {
                ans = j + 1;
            }
        }
        std::cout << ans << "\n";
    }

    return 0;
}
