#include <bits/stdc++.h>

void solve() {
    int n, xk, yk, xd, yd;
    std::cin >> n >> xk >> yk >> xd >> yd;

    int ans;
    if (xk == xd) {
        if (yk > yd) {
            ans = n - yd;
        } else {
            ans = yd;
        }
    } else if (yk == yd) {
        if (xk > xd) {
            ans = n - xd;
        } else {
            ans = xd;
        }
    } else {
        if (xk <= xd && yk <= yd) {
            ans = std::max(xd, yd);
        }
        if (xk >= xd && yk <= yd) {
            ans = std::max(n - xd, yd);
        }
        if (xk <= xd && yk >= yd) {
            ans = std::max(xd, n - yd);
        }
        if (xk >= xd && yk >= yd) {
            ans = std::max(n - xd, n - yd);
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