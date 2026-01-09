#include <bits/stdc++.h>

const int P = 1'000'000'007;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> s(n);
    bool infty = false;
    int min = 1'000'000'000;
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
        if (s[i] >= 31) {
            infty = true;
            min = std::min(min, s[i]);
        }
    }

    unsigned stat = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] >= 31) {
            continue;
        }
        stat |= (1 << (s[i] - 1));
    }

    std::vector<int> step(32), mul(32);
    step[1] = 1;
    mul[1] = 1;
    for (int i = 2; i <= 31; ++i) {
        step[i] = 2 * step[i - 1] + 1;
        mul[i] = 1LL * i * mul[i - 1] % P * mul[i - 1] % P;
    }

    auto first_zero = [](unsigned int x) {
        int c = 1;
        while (x > 0 && x & 1) {
            x >>= 1;
            ++c;
        }
        return c;
    };

    auto first_one = [](unsigned int x) {
        int c = 1;
        while (x > 0 && !(x & 1)) {
            x >>= 1;
            ++c;
        }
        return c;
    };

    int ans = 1;
    while (k > 0) {
        if ((stat & 1) == false) {
            int l = first_one(stat);
            if (stat == 0) {
                if (infty) {
                    l = min;
                    stat = 1 << 30;
                    infty = false;
                } else {
                    break;
                }
            }
            ans = 1LL * ans * l % P;
            --stat;
            --k;
        } else {
            int idx = std::upper_bound(step.begin(), step.begin() + first_zero(stat), k) - step.begin() - 1;
            ans = 1LL * ans * mul[idx] % P;
            stat -= (1 << idx) - 1;
            k -= step[idx];
        }
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}