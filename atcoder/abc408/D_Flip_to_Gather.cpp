#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int N;
    std::cin >> N;

    std::string S;
    std::cin >> S;

    std::vector<int> C(N + 1);
    for (int i = 0; i < N; ++i) {
        C[i + 1] = C[i] + ((S[i] == '0') ? 1 : -1);
    }

    int max = -1E9, ans = 1E9;
    for (int i = 0; i <= N; ++i) {
        max = std::max(max, C[i]);
        ans = std::min(ans, C[i] - max);
    }

    std::cout << ans + std::count(S.begin(), S.end(), '1') << "\n";
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
