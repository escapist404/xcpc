#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, J, K;
            std::cin >> N >> J >> K;
            std::vector<int> A(N);
            for (auto& i : A) std::cin >> i;
            --J;
            
            if (K >= 2 || *std::max_element(A.begin(), A.end()) == A[J]) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
    
}