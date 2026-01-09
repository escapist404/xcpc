#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            int A, B, C, D;
            long long answer = 0;
            for (int i = 0; i < n; ++i) {
                std::cin >> A >> B >> C >> D;
                if (A > C) answer += A - C;
                if (B > D) answer += std::min(A, C) + B - D;
            }
            std::cout << answer << "\n";
        }();
    }
    return 0;
}
