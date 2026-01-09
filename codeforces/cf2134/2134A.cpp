#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, A, B;
            std::cin >> N >> A >> B;

            if (N % 2 == B % 2 && N % 2 == A % 2) {
                std::cout << "YES\n";
            } else if (N % 2 == B % 2 && B > A) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }

    return 0;
}
