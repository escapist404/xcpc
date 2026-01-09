#include <bits/stdc++.h>

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

void solve() {
    int a[11] {};
    for (int i = 1; i <= 9; ++i) {
        std::cin >> a[i];
    }

    int d = std::min(a[1], a[2]);
    a[3] += d;
    a[2] -= d;
    a[1] -= d;
    a[2] += a[1] / 2;
    a[1] -= a[1] / 2 * 2;
    if (a[1] == 1) {
        for (int i = 2; i <= 9; ++i) {
            if (a[i] != 0) {
                a[i] -= 1;
                a[1] -= 1;
                a[i + 1] += 1;
                break;
            }
        }
    }

    int ans = 1;
    for (int i = 2; i <= 10; ++i) {
        ans = 1LL * ans * power(i, a[i]) % P;
    }

    std::cout << ans << "\n";
}

/*
7
5 3 0 0 0 0 0 0 0
4 1 1 1 0 0 0 0 0
1 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 2
99 88 77 66 55 44 33 22 11
100 90 80 70 60 50 40 30 20
*/

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
