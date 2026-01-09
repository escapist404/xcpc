#include <vector>
#include <iostream>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            for (auto& i : A) {
                std::cin >> i;
            }

            int zero = 0, one = 0;
            for (int i = 0; i < N; ++i) {
                if (A[i] == 0) zero++;
                else if (A[i] == 1) one++;
            }

            int S = std::accumulate(A.begin(), A.end(), 0);
            while (zero && one) {
                ++S;
                --zero, --one;
            }
            while (zero) {
                ++S;
                --zero;
            }
            std::cout << S << "\n";
        }();
    }
}
