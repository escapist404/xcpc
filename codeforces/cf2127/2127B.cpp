#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, X;
            std::cin >> N >> X;
            std::string S;
            std::cin >> S;

            --X;
            int L = X, R = X;
            for (; R < N && S[R] == '.'; ++R);
            for (; L >= 0 && S[L] == '.'; --L);

            std::cout << std::max(std::min(X + 1, N - R + 1), std::min(N - X, L + 2)) << "\n";
        }();
    }
}