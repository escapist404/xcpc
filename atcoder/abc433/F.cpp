#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

const int D = 10;
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
    std::string s;
    std::cin >> s;

    int n = s.size();

    std::vector<int> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }

    std::vector<int> ifac(n + 1);
    ifac[n] = power(fac[n], P - 2);
    for (int i = n - 1; i >= 0; --i) {
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % P;
    }

    auto comb = [&](int all, int choose) {
        return choose <= all ? 1LL * fac[all] * ifac[choose] % P * ifac[all - choose] % P : 0;
    };

    std::vector<std::array<int, D>> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i];
        p[i + 1][s[i] - '0']++;
    }

    std::array<int, D> a = p[n];

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '9') {
            continue;
        }
        int c = p[i][s[i] - '0'];
        int d = a[s[i] - '0' + 1] - p[i + 1][s[i] - '0' + 1];
        (ans += comb(c + d, c + 1)) %= P;
    }

    std::cout << ans << "\n";

    return 0;
}
