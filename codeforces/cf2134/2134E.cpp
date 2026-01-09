#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            auto throwOperation = [](int x) {
                std::cout << "throw " << x + 1 << std::endl;
                int y;
                std::cin >> y;
                return y;
            };

            auto swapOperation = [](int x) {
                std::cout << "swap " << x + 1 << std::endl;
            };
            
            int N;
            std::cin >> N;
            
            std::vector<int> A(N), F(N + 2);

            auto report = [&]() {
                std::cout << "! ";
                for (int i = 0; i < N; ++i) {
                    std::cout << A[i] << " ";
                }
                std::cout << std::endl;
            };

            for (int i = N - 1; i >= 0; --i) {
                if (F[i + 1] != F[i + 2]) {
                    int result = throwOperation(i);
                    if (result == F[i + 1] + 1) {
                        A[i] = 1;
                    } else {
                        A[i] = 2;
                    }
                    F[i] = result;
                } else {
                    F[i] = F[i + 1] + 1;
                }
            }

            for (int i = 0; i < N - 1; ++i) {
                if (A[i] == 0) {
                    swapOperation(i);
                    if (throwOperation(i + 1) == F[i + 2] + 1) {
                        A[i] = 1;
                    } else {
                        A[i] = 2;
                    }
                }
            }

            swapOperation(N - 2);
            if (throwOperation(N - 2) == 1) {
                A[N - 1] = 2;
            } else {
                A[N - 1] = 1;
            }

            report();
        }();
    }

    return 0;
}
