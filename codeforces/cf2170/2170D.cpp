#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;

    int type[] = {0, 0, 0};
    for (int i = 0, j; i < n; i += j) {
        j = 0;
        while (i + j < n && s[i] == s[i + j]) {
            ++j;
        }
        if (s[i] != '?') {
            continue;
        }

        bool fr = (i > 0 && s[i - 1] == 'I');
        bool bk = (i + j < n && (s[i + j] == 'V' || s[i + j] == 'X'));

        if (fr) {
            if (bk) {
                type[0] += j / 2;
                type[1] += j % 2;
                type[2] += j / 2;
            } else {
                type[0] += (j - 1) / 2;
                type[1] += (j - 1) % 2;
                type[2] += (j + 1) / 2;
            }
        } else {
            if (bk) {
                type[0] += (j + 1) / 2;
                type[1] += (j + 1) % 2;
                type[2] += (j - 1) / 2;
            } else {
                type[0] += j / 2;
                type[1] += j % 2;
                type[2] += j / 2;
            }
        }
    }

    int cnt_q = 0, ori = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'V') {
            ori += 5;
        } else if (s[i] == 'X') {
            ori += 10;
        } else if (s[i] == 'I') {
            if (i < n - 1 && s[i + 1] != 'I') {
                ori -= 1;
            } else {
                ori += 1;
            }
        } else {
            ++cnt_q;
        }
    }

    while (q--) {
        int cx, cv, ci;
        std::cin >> cx >> cv >> ci;

        int ans = ori, filled = 0;
        ans += (-1) * std::min(ci, type[0]);
        filled += std::min(ci, type[0]);
        ci -= std::min(ci, type[0]);
        ans += std::min(ci, type[1]);
        filled += std::min(ci, type[1]);
        ci -= std::min(ci, type[1]);
        ans += 3 * std::min(ci, type[2]);
        filled += std::min(ci, type[2]);
        ci -= std::min(ci, type[2]);
        ans += 5 * std::min(cnt_q - filled, cv);
        filled += std::min(cnt_q - filled, cv);
        ans += 10 * std::min(cnt_q - filled, cx);
        filled += std::min(cnt_q - filled, cx);

        std::cout << ans << "\n";
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
