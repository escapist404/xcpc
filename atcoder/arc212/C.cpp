#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using i64 = long long;

const int P = 998244353;

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
    int n, m;
    std::cin >> n >> m;
    if (n < m) {
        std::cout << "0\n";
        return 0;
    }

    std::vector<int> fac(n + m);
    fac[0] = 1;
    for (int i = 1; i <= n + m - 1; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }

    std::vector<int> ifac(n + m);
    ifac[n + m - 1] = power(fac[n + m - 1], P - 2);
    for (int i = n + m - 2; i >= 0; --i) {
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % P; 
    }

    auto binom = [fac, ifac](const int all, const int choose) {
        return all < choose ? 0LL : 1LL * fac[all] * ifac[choose] % P * ifac[all - choose] % P;
    };

    int im = power(m, P - 2);
    int s = m + (n - m) % 2;
    int ans = 0;
    for (int k = s; k <= n; k += 2) {
        int A = binom((n - k) / 2 + m - 1, m - 1);
        int B = binom(k + m - 1, 2 * m - 1);
        (ans += 1LL * A * B % P) %= P;
    }

    ans = 1LL * ans * power(2, m) % P;
    std::cout << ans << "\n";
    return 0;
}
