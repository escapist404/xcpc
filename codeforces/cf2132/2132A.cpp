#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, M;
            std::string S, T, C;
            std::cin >> N >> S >> M >> T >> C;
            for (int i = 0; i < M; ++i) {
                if (C[i] == 'D') {
                    S.insert(S.end(), T[i]);
                } else {
                    S.insert(S.begin(), T[i]);
                }
            }
            std::cout << S << "\n";
        }();
    }
}