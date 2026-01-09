#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, k;
            std::cin >> n >> k;
            std::vector<int> a(n);
            for (auto& i : a) std::cin >> i;
            a.insert(a.begin(), 1);

            int answer = 0;
            while (a.size()) {
                int count = 0;
                while (a.back() == 0 && count < k) {
                    a.pop_back();
                    ++count;
                }
                a.pop_back();
                if (count == k) {
                    ++answer;
                }
            }
            std::cout << answer << "\n";
        }();
    }
}