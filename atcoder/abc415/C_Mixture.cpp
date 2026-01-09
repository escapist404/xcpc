#include <bits/stdc++.h>

void solve() {
    int N;
    std::cin >> N;

    std::string S;
    std::cin >> S;

    std::vector<int> f(1 << N);
    f[0] = 1;
    for (int i = 1; i < 1 << N; ++i) {
        if (S[i - 1] == '1') {
            continue;
        }
        for (int j = 0; j < N; ++j) {
            if (((i >> j) & 1) == false) {
                continue;
            }
            f[i] |= f[i ^ (1 << j)];
        }
    }

    if (f[(1 << N) - 1]) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
