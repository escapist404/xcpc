#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;
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

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> fac(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }

    std::vector<int> ifac(n + 1, 1);
    ifac[n] = power(fac[n], P - 2);
    for (int i = n - 1; i >= 0; --i) {
        ifac[i] = 1LL * ifac[i + 1] * (i + 1) % P;
    }

    std::vector<int> a(n + 1);
    for (int i = 0; i <= n; ++i) {
        std::cin >> a[i];
    }

    int A = *std::max_element(a.begin() + 1, a.end());
    int e = std::count(a.begin() + 1, a.end(), A);
    int l = n - e;
    i64 s = std::accumulate(a.begin() + 1, a.end(), 0LL);
    int r = (int)std::min(a[0] + s - 1LL * e * A - 1LL * l * (A - 1), (i64)l);
    
    if (r < 0) {
        std::cout << "0\n";
    } else {
        int a = e + r;
        int b = l - r;
        std::cout << 1LL * fac[l] * ifac[r] % P * ifac[l - r] % P * fac[a] % P * fac[b] % P << "\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
