#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    int c = 0;
    for (const auto& i : s) {
        c += std::count(i.begin(), i.end(), '1');
    }

    if (c == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << "YN"[s[i][j] == '1'];
            }
            std::cout << "\n";
        }
    } else if (c == n * m - 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << "YN"[s[i][j] == '0'];
            }
            std::cout << "\n";
        }
    } else {
        for (int i = 0; i < n; ++i) {
            std::cout << std::string('Y', m) << "\n";
        }
    }
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
