#include <bits/stdc++.h>

void solve() {
    using i64 = long long;
    i64 c, d;
    std::cin >> c >> d;

    auto len = [](i64 x) {
        int c = 0;
        while (x) {
            x /= 10;
            c++;
        }
        return c;
    };

    auto cs = std::to_string(c), ds = std::to_string(d);
    
    i64 ans = 0;

    if (len(c + 1) == len(c + d)) {
        i64 lo = std::stoll(cs + std::to_string(c + 1));
        i64 hi = std::stoll(cs + std::to_string(c + d));

        ans += (i64)sqrtl(hi) - (i64)sqrtl(lo);
        if ((i64)sqrtl(lo) * (i64)sqrtl(lo) == lo) {
            ++ans;
        }

        std::cout << ans << "\n";
        return;
    }

    i64 lo = std::stoll(cs + std::to_string(c + 1));
    i64 hi = std::stoll(cs + std::string(len(c + 1), '9'));

    ans += (i64)sqrtl(hi) - (i64)sqrtl(lo);
    if ((i64)sqrtl(lo) * (i64)sqrtl(lo) == lo) {
        ++ans;
    }

    for (int i = len(c + 1) + 1; i < len(c + d); ++i) {
        lo = std::stoll(cs + "1" + std::string(i - 1, '0'));
        hi = std::stoll(cs + std::string(i, '9'));
        ans += (i64)sqrtl(hi) - (i64)sqrtl(lo);
        if ((i64)sqrtl(lo) * (i64)sqrtl(lo) == lo) {
            ++ans;
        }
    }

    lo = std::stoll(cs + "1" + std::string(len(c + d) - 1, '0'));
    hi = std::stoll(cs + std::to_string(c + d));

    ans += (i64)sqrtl(hi) - (i64)sqrtl(lo);
    if ((i64)sqrtl(lo) * (i64)sqrtl(lo) == lo) {
        ++ans;
    }

    std::cout << ans << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}