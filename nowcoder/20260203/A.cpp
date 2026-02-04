#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

const int P = 998244353;

constexpr int power(int base, int exp) {
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

constexpr int inv(int base) {
    return power(base, P - 2);
}

const int I100 = inv(100);

constexpr int mul(const int x, const int y) {
    return 1LL * x * y % P;
}

template <typename... Args>
constexpr int mul(const int x, Args... args) {
    return 1LL * x * mul(args...) % P;
}

void solve() {
    int c;
    std::cin >> c;

    int p[7] = {};
    for (auto& i : p) {
        std::cin >> i;
    }

    int q[7][2];
    for (int i = 0; i < 7; ++i) {
        q[i][1] = 1LL * p[i] * I100 % P;
        q[i][0] = 1LL * (100 - p[i]) * I100 % P;
    }

    int dgt[10];
    dgt[0] = mul(q[0][1], q[1][1], q[2][1], q[3][0], q[4][1], q[5][1], q[6][1]);
    dgt[1] = mul(q[0][0], q[1][0], q[2][1], q[3][0], q[4][0], q[5][1], q[6][0]);
    dgt[2] = mul(q[0][1], q[1][0], q[2][1], q[3][1], q[4][1], q[5][0], q[6][1]);
    dgt[3] = mul(q[0][1], q[1][0], q[2][1], q[3][1], q[4][0], q[5][1], q[6][1]);
    dgt[4] = mul(q[0][0], q[1][1], q[2][1], q[3][1], q[4][0], q[5][1], q[6][0]);
    dgt[5] = mul(q[0][1], q[1][1], q[2][0], q[3][1], q[4][0], q[5][1], q[6][1]);
    dgt[6] = mul(q[0][1], q[1][1], q[2][0], q[3][1], q[4][1], q[5][1], q[6][1]);
    dgt[7] = mul(q[0][1], q[1][0], q[2][1], q[3][0], q[4][0], q[5][1], q[6][0]);
    dgt[8] = mul(q[0][1], q[1][1], q[2][1], q[3][1], q[4][1], q[5][1], q[6][1]);
    dgt[9] = mul(q[0][1], q[1][1], q[2][1], q[3][1], q[4][0], q[5][1], q[6][1]);

    int ans = 0;
    for (int a = 0; a <= c; ++a) {
        int b = c - a;
        int da[4] = {a / 1000, a % 1000 / 100, a % 100 / 10, a % 10};
        int db[4] = {b / 1000, b % 1000 / 100, b % 100 / 10, b % 10};
        ans += mul(dgt[da[0]], dgt[da[1]], dgt[da[2]], dgt[da[3]], dgt[db[0]], dgt[db[1]], dgt[db[2]], dgt[db[3]]);
        ans %= P;
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
