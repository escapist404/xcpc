#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            for (auto& i : A) std::cin >> i;

            int first = A[0], last = A[N - 1];
            std::sort(A.begin(), A.end());
            int current = first, answer = 1;
            if (first >= last) {
                std::cout << 2 << "\n";
                return;
            }
            while (current < last) {
                int index = std::prev(std::upper_bound(A.begin(), A.end(), 2 * current)) - A.begin();
                if (A[index] > current) {
                    current = A[index];
                    ++answer;
                } else {
                    std::cout << -1 << "\n";
                    return;
                }
            }
            std::cout << answer << "\n";
        }();
    }
    
    return 0;
}