#include <bits/stdc++.h>

namespace interactor {
bool ask(int i, int x) {
    std::cout << "? " << i + 1 << " " << x << std::endl;
    bool ret;
    std::cin >> ret;
    return ret;
}
void report(int x) {
    std::cout << "! " << x << std::endl;
}
}  // namespace interactor

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> cand(n - 1), ans(n);
    std::iota(cand.begin(), cand.end(), 0);
    std::iota(ans.begin(), ans.end(), 1);

    for (int i = 0; (1 << i) < 2 * n; ++i) {
        int x = 1 << i;
        std::vector<int> s, t;
        for (const auto& j : cand) {
            if (interactor::ask(j, x)) {
                t.push_back(j);
            } else {
                s.push_back(j);
            }
        }
        std::vector<int> u, v;
        for (const auto& j : ans) {
            if (j & x) {
                v.push_back(j);
            } else {
                u.push_back(j);
            }
        }
        if (t.size() != v.size()) {
            cand = t;
            ans = v;
        } else {
            cand = s;
            ans = u;
        }
    }

    interactor::report(ans[0]);
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}