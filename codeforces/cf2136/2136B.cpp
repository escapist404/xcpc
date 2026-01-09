#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, K;
            std::cin >> N >> K;

            std::string S;
            std::cin >> S;
            
            std::vector<int> P(N);
            int max_len = 0;
            for (int i = 0, min = 1, max = N, con = 0; i < N; ++i) {
                if (S[i] == '1') {
                    P[i] = min++;
                    ++con;
                } else {
                    P[i] = max--;
                    con = 0;
                }
                max_len = std::max(con, max_len);
            }
            
            if (max_len >= K) {
                std::cout << "NO\n";
            } else {
                std::cout << "YES\n";
                for (int i = 0; i < N; ++i) {
                    std::cout << P[i] << " \n"[i == N - 1];
                }
            }
        }();
    }
}