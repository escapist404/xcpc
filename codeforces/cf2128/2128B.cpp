#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            std::list<int> P;
            for (int i = 0; i < n; ++i) {
                int x;
                std::cin >> x;
                P.push_back(x);
            }

            std::string S;
            bool sign = false;
            while (P.size()) {
                // std::cerr << P.front() << " " << P.back() << "\n";
                if (sign) {
                    if (P.front() > P.back()) {
                        P.pop_back();
                        S.push_back('R');
                    } else {
                        P.pop_front();
                        S.push_back('L');
                    }
                } else {
                    if (P.front() < P.back()) {
                        P.pop_back();
                        S.push_back('R');
                    } else {
                        P.pop_front();
                        S.push_back('L');
                    }
                }
                sign ^= 1;
            }
            std::cout << S << "\n";
        }();
    }
}
