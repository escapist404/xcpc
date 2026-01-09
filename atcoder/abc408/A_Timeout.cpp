#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, S;
    std::cin >> N >> S;

    int c = 0;
    bool ans = true;
    for (int i = 0; i < N; ++i) {
        int t;
        std::cin >> t;

        if (t - c > S) {
            ans = false;
        }
        c = t;
    }

    if (ans) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
