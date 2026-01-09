#include <vector>
#include <iostream>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            // std::cin.tie(nullptr)->sync_with_stdio(false);
            int N;
            std::cin >> N;
            std::vector<int> P(N), inv(N);
            
            for (int i = 0; i < N; ++i) {
                std::cin >> P[i];
                --P[i];
                inv[P[i]] = i;
            }
            
            
            using i64 = long long;
            i64 answer = 0;
            std::vector<int> c(N);
            for (int v = N - 1; v >= 0; --v) {
                // std::cerr << "YES\n";
                int left = 0, right = 0;
                for (int j = 0; j < inv[v]; ++j) {
                    left += c[j];
                }
                for (int j = inv[v] + 1; j < N; ++j) {
                    right += c[j];
                }
                answer += std::min(left, right);
                ++c[inv[v]];
            }

            std::cout << answer << "\n";            
        }();
    }
}
