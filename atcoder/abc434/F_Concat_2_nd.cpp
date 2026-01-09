#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> get_fail(const std::string& s) {
    std::vector<int> fail = {0};
    for (int i = 1, j = 0; i < s.size(); ++i, j = fail[i - 1]) {
        while (j && s[i] != s[j])
            j = fail[j - 1];
        fail.push_back(j + (s[i] == s[j]));
    }
    return fail;
}

void solve() {
    int N;
    std::cin >> N;

    std::vector<std::string> S(N);
    for (auto& s : S) {
        std::cin >> s;
    }

    std::vector<std::string> SS(N);
    for (int i = 0; i < N; ++i) {
        SS[i] = S[i] + S[i];
    }

    std::vector<int> P(N);
    std::iota(P.begin(), P.end(), 0);
    std::sort(P.begin(), P.end(), [&](int x, int y) {
        return SS[x] < SS[y];
    });

    bool ok = false;

    

    if (ok == false) {
        std::swap(P[N - 2], P[N - 1]);
    }
    for (int i = 0; i < N; ++i) {
        std::cout << S[P[i]];
    }
    std::cout << "\n";
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
