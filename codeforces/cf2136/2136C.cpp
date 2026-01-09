#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <queue>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            std::vector<std::queue<int>> last(N + 1);
            for (int i = 0; i < N; ++i) {
                std::cin >> A[i];
            }

            std::vector<int> f(N + 1);
            for (int i = N - 1; i >= 0; --i) {
                last[A[i]].push(i);
                f[i] = f[i + 1];
                if (last[A[i]].size() == A[i]) {
                    f[i] = std::max(f[i], f[last[A[i]].front() + 1] + A[i]);
                    last[A[i]].pop();
                }
            }

            std::cout << f[0] << "\n";
        }();
    }
}
