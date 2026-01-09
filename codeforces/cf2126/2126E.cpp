#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            
            using i64 = long long;

            std::vector<i64> p(n), s(n);
            for (auto& i : p) std::cin >> i;
            for (auto& i : s) std::cin >> i;

            std::vector<i64> a(n);
            for (int i = 0; i < n; ++i) {
                a[i] = std::lcm(p[i], s[i]);
            }

            std::vector<i64> P(a), S(a);
            for (int i = 1; i < n; ++i) {
                P[i] = std::gcd(P[i - 1], P[i]);
            }
            for (int i = n - 2; i >= 0; --i) {
                S[i] = std::gcd(S[i + 1], S[i]);
            }

            if (P == p && S == s) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}