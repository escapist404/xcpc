#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int A, B, C, D;
            std::cin >> A >> B >> C >> D;

            C -= A, D -= B;
            if (A > B) {
                std::swap(A, B);
            }
            if (C > D) {
                std::swap(C, D);
            }
            if (B <= 2 * (A + 1) && D <= 2 * (C + 1)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}