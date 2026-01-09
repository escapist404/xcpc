#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, c;
            std::cin >> n >> c;
            std::vector<int> A(n);
            for (auto& i : A) std::cin >> i;

            int answer = 0;
            std::sort(A.begin(), A.end());
            while (A.size()) {
                while (A.size() && A.back() > c) {
                    A.pop_back();
                    ++answer;
                }
                if (A.size()) A.pop_back();
                for (auto& i : A) i *= 2;
            }

            std::cout << answer << "\n";
        }();
    }
}
