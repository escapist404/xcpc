#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        int tr = n * n;
        int white = 0;
        int black = std::count(s[i].begin(), s[i].end(), '#');
        for (int j = n; j >= 0; --j) {
            tr = std::min(tr, f[i][j]);
            f[i + 1][j] = tr + black + white;
            if (j > 0) {
                if (s[i][j - 1] == '.') {
                    white++;
                } else {
                    black--;
                }
            }
        }
    }

    std::cout << *std::min_element(f[n].begin(), f[n].end()) << "\n";

    return 0;
}
