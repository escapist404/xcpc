#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, K;
            std::cin >> N >> K;
            std::vector<std::pair<int, int>> P(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> P[i].first;
            }
            for (int i = 0; i < N; ++i) {
                std::cin >> P[i].second;
                if (P[i].second < P[i].first) std::swap(P[i].first, P[i].second);
            }

            std::sort(P.begin(), P.end(), [](auto x, auto y) {
                if (x.first != y.first) return x.first < y.first;
                return x.second > y.second;
            });

            i64 answer = 0;
            for (int i = 0; i < N; ++i) {
                answer += P[i].second - P[i].first;
            }

            i64 min = 2E9;
            for (int i = 1; i < N; ++i) {
                min = std::max(std::min((i64)P[i].first - P[i - 1].second, min), 0LL);
            }
            std::cout << answer + 2 * min << "\n";
        }();
    }
}