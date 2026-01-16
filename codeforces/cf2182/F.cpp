#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;
const int V = 60;
const int P = 998'244'353;

int power(int base, int exp) {
    int ret = 1;
    while (exp) {
        if (exp & 1) {
            ret = 1LL * ret * base % P;
        }
        base = 1LL * base * base % P;
        exp >>= 1;
    }
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;

    std::vector<int> c(V + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        c[x]++;
    }

    std::vector<int> fac(n + m + 1);
    fac[0] = 1;
    for (int i = 1; i <= n + m; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }

    std::vector<int> ifac(n + m + 1);
    ifac[n + m] = power(fac[n + m], P - 2);
    for (int i = n + m - 1; i >= 0; --i) {
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % P;
    }

    std::vector<int> pow2(n + m + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n + m; ++i) {
        pow2[i] = 1LL * pow2[i - 1] * 2 % P;
    }

    auto comb = [&](int choose, int all) {
        return choose <= all ? 1LL * fac[all] * ifac[choose] % P * ifac[all - choose] % P : 0;
    };

    auto comb_gt = [&](int choose, int all) {
        if (choose >= all) {
            return 0;
        }
        int ret = pow2[all];
        for (int i = 0; i <= choose; ++i) {
            ret -= comb(i, all);
            if (ret < 0) {
                ret += P;
            }
        }
        return ret;
    };

    while (m--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int x;
            std::cin >> x;
            c[x]++;
        } else if (type == 2) {
            int x;
            std::cin >> x;
            c[x]--;
        } else {
            i64 x;
            std::cin >> x;

            std::vector<int> r(V + 1);
            int shift = 0;
            for (int i = V; i >= 0; --i) {
                if ((x >> i) & 1) {
                    r[i + shift]++;
                    shift++;
                }
            }

            int ans = 0;
            int gt = 1;
            int lt = std::accumulate(c.begin(), c.end(), 0);

            for (int i = V; i >= 0; --i) {
                lt -= c[i];
                (ans += 1LL * gt * comb_gt(r[i], c[i]) % P * pow2[lt] % P) %= P;
                gt = 1LL * gt * comb(r[i], c[i]) % P;
            }

            (ans += gt) %= P;

            std::cout << ans << "\n";
        }
    }

    return 0;
}
