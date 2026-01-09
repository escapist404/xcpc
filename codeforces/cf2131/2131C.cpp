#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, k;
            std::cin >> n >> k;
            std::vector<int> S;
            std::map<int, int> T;
            for (int i = 0; i < n; ++i) {
                int x;
                std::cin >> x;
                S.push_back(x);
            }

            for (int i = 0; i < n; ++i) {
                int x;
                std::cin >> x;
                T[x % k]++;
                T[(-(x % k) + k) % k]++;
            }

            bool ans = true;
            for (int i = 0; i < n; ++i) {
                if (T[S[i] % k] >= 1) {
                    --T[S[i] % k];
                    --T[(-(S[i] % k) + k) % k];
                } else {
                    ans = false;
                }
            }

            if (ans) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}