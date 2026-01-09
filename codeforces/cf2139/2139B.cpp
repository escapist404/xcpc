#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, m;
            std::cin >> n >> m;
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }

            std::sort(a.begin(), a.end());

            long long answer = 0;
            for (int i = n - 1; i >= 0 && m >= 0; --i) {
                answer += 1LL * a[i] * m;
                --m;
            }

            std::cout << answer << "\n";
        }();
    }

    return 0;
}