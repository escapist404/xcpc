#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int h, w;
    std::cin >> h >> w;

    std::vector<int> s(h);
    for (int i = 0; i < h; ++i) {
        std::string t;
        std::cin >> t;
        for (int j = 0; j < w; ++j) {
            if (t[j] == '#') {
                s[i] ^= 1 << j;
            }
        }
    }

    std::vector<std::vector<int>> f(h, std::vector<int>(1 << w, 1E9));
    for (int S = 0; S < 1 << w; ++S) {
        if (S & ~s[0]) {
            continue;
        }
        f[0][S] = __builtin_popcount((~S) & s[0]);
    }

    for (int i = 1; i < h; ++i) {
        for (int S = 0; S < 1 << w; ++S) {
            if (S & (~s[i - 1])) {
                continue;
            }
            for (int T = 0; T < 1 << w; ++T) {
                if (T & (~s[i])) {
                    continue;
                }
                if ((S & T) & ((S & T) << 1)) {
                    continue;
                }
                f[i][T] = std::min(f[i - 1][S] + __builtin_popcount((~T) & s[i]), f[i][T]);
            }
        }
    }

    std::cout << *std::min_element(f.back().begin(), f.back().end()) << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
