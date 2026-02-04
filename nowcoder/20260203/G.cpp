#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

void solve() {
    i64 l, r;
    std::cin >> l >> r;

    auto find = [&](i64 l, i64 r) -> i64 {
        std::string ans;
        while (r - l >= 9) {
            ans += "9";
            l /= 10;
            r = (r % 10 == 9) ? (r / 10) : (r / 10 - 1);
        }
        std::string dans = "0";
        for (i64 i = l; i <= r; ++i) {
            auto s = std::to_string(i);
            std::reverse(s.begin(), s.end());
            dans = std::max(dans, s);
        }
        if (dans != "0") {
            ans += dans;
        }
        return std::stoll(ans);
    };

    std::vector<i64> seq = {l};
    for (i64 t = 1, e = 0; e <= 15; ++e, t *= 10) {
        if (l <= t - 1 && t <= r) {
            seq.push_back(t - 1);
            seq.push_back(t);
        }
    }
    seq.push_back(r);

    i64 fans = 0;
    for (int i = 0; i < (int)seq.size(); i += 2) {
        fans = std::max(fans, find(seq[i], seq[i + 1]));
    }

    std::cout << fans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
