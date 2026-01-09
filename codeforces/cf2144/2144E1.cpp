#include <bits/stdc++.h>

const int P = 998'244'353;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> view_l = {0}, view_r = {0};
    for (int i = 0; i < n; ++i) {
        if (view_l.back() < a[i]) {
            view_l.push_back(a[i]);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (view_r.back() < a[i]) {
            view_r.push_back(a[i]);
        }
    }

    std::vector<int> sub_l(view_l.size()), sub_r(view_r.size());
    std::vector<int> comb_l(n), comb_r(n);

    sub_l[0] = sub_r[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)view_l.size(); ++j) {
            if (view_l[j] >= a[i]) {
                (sub_l[j] += sub_l[j]) %= P;
            }
            if (view_l[j] == a[i]) {
                (sub_l[j] += sub_l[j - 1]) %= P;
            }
        }
        if (view_l.back() == a[i]) {
            comb_l[i] = sub_l[(int)sub_l.size() - 2];
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < (int)view_r.size(); ++j) {
            if (view_r[j] >= a[i]) {
                (sub_r[j] += sub_r[j]) %= P;
            }
            if (view_r[j] == a[i]) {
                (sub_r[j] += sub_r[j - 1]) %= P;
            }
        }
        if (view_r.back() == a[i]) {
            comb_r[i] = sub_r[(int)sub_r.size() - 2];
        }
    }

    std::vector<int> p2(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        p2[i] = 1LL * p2[i - 1] * 2 % P;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            (ans += 1LL * comb_l[i] * comb_r[j] % P * p2[std::max(j - i - 1, 0)] % P) %= P;
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