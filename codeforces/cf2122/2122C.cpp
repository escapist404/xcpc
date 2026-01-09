#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            std::vector<std::pair<int, int>> X(n), Y(n);

            for (int i = 0; i < n; ++i) {
                std::cin >> X[i].first >> Y[i].first;
                X[i].second = i, Y[i].second = i;
            }

            std::sort(X.begin(), X.end());
            std::sort(Y.begin(), Y.end());

            std::vector<int> P[4], S(n);
            for (int i = 0; i < n / 2; ++i) {
                S[X[i].second] ^= 1;
                S[Y[i].second] ^= 2;
            }

            for (int i = 0; i < n; ++i) {
                P[S[i]].push_back(i);
            }

            for (int s = 0; s < 2; ++s) {
                for (int i = 0; i < P[s].size(); ++i) {
                    std::cout << P[s][i] + 1 << " " << P[3 ^ s][i] + 1 << "\n";
                }
            }
        }();
    }
    return 0;
}
