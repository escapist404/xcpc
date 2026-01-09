#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, X, Y;
    std::cin >> N >> X >> Y;

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    i64 L = -1, R = 1E18 + 1;
    for (int i = 0; i < N; ++i) {
        L = std::max(L, 1LL * A[i] * X);
        R = std::min(R, 1LL * A[i] * Y);
    }

    if (L > R) {
        std::cout << "-1\n";
        return 0;
    }

    i64 ans = 0;
    bool ok = true;
    for (int i = 0; i < N; ++i) {
        if ((R - 1LL * A[i] * X) % (Y - X) != 0) {
            ok = false;
        }
        ans += (R - 1LL * A[i] * X) / (Y - X);
    }

    if (ok == false) {
        std::cout << "-1\n";
        return 0;
    }
    
    std::cout << ans << "\n";
    return 0;
}
