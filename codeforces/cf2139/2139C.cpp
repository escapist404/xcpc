#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int k;
            using i64 = long long;
            i64 x;
            std::cin >> k >> x;

            std::vector<int> op;
            while (x != 1LL << k) {
                if (x < 1LL << k) {
                    x <<= 1;
                    op.push_back(1);
                } else {
                    x = (2LL << k) - 2 * ((2LL << k) - x);
                    op.push_back(2);
                }
            }

            std::cout << op.size() << "\n";
            for (int i = (int)op.size() - 1; i >= 0; --i) {
                std::cout << op[i] << " ";
            }

            std::cout << "\n";
        }();
    }

    return 0;
}