#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << "! 0" << std::endl;
        return;
    }

    auto ask = [&](int k) -> std::vector<int> {
        std::cout << "? " << k + 1 << std::endl;
        int l;
        std::cin >> l;
        std::vector<int> r(l);
        for (int i = 0; i < l; ++i) {
            std::cin >> r[i];
            --r[i];
        }
        return r;
    };

    std::vector<std::pair<int, int>> e;
    std::vector<int> d(n), v(n);
    d[0] = 1;
    std::vector<int> r = {0};
    int c = 1;
    while (true) {
        auto s = ask(c);
        if (s.empty()) {
            break;
        }
        for (int i = 0; i < (int)r.size(); ++i) {
            if (i < (int)s.size() && r[i] != s[i]) {
                v[r[i]] = 1;
            } else if (i >= (int)s.size()) {
                v[r[i]] = 1;
            }
        }
        r = s;
        if (s.size() >= 2) {
            e.emplace_back(s[(int)s.size() - 2], s[(int)s.size() - 1]);
        }
        if (v[s.back()] == 0) {
            c++;
            for (auto i : s) {
                if (v[i] == 0) {
                    d[i]++;
                }
            }
        } else {
            c += d[s.back()];
            for (auto i : s) {
                if (v[i] == 0) {
                    d[i] += d[s.back()];
                }
            }
        }
    }

    std::cout << "! " << e.size() << std::endl;
    for (auto [u, v] : e) {
        std::cout << u + 1 << " " << v + 1 << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
