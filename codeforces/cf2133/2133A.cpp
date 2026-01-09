#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> A[i];
            }
            std::set<int> S(A.begin(), A.end());
            if (S.size() != A.size()) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}