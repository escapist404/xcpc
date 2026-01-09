#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            using i64 = long long;

            int N;
            std::cin >> N;


            std::vector<int> prime;
            std::vector<bool> visit(N + 1);

            for (int i = 2; i <= N; ++i) {
                if (visit[i] == false) {
                    prime.push_back(i);
                }
                for (const auto j : prime) {
                    if ((i64)i * j > N) {
                        break;
                    }
                    visit[i * j] = true;
                    if (i % j == 0) {
                        break;
                    }
                }
            }

            std::vector<std::vector<int>> cycle;
            int M = prime.size();
            visit = std::vector<bool>(N + 1);
            for (int i = M - 1; i >= 0; --i) {
                std::vector<int> current = {prime[i]};
                for (int j = 2; j * prime[i] <= N; ++j) {
                    if (visit[j * prime[i]] == false) {
                        current.push_back(j * prime[i]);
                        visit[j * prime[i]] = true;
                    }
                }
                cycle.push_back(current);
            }

            std::vector<int> P(N + 1);
            std::iota(P.begin(), P.end(), 0);
            for (auto C : cycle) {
                int S = C.size();
                for (int i = 1; i < S; ++i) {
                    std::swap(P[C[i]], P[C[i - 1]]);
                }
            }

            for (int i = 1; i < N + 1; ++i) {
                std::cout << P[i] << " \n"[i == N];
            }
        }();
    }
    
}