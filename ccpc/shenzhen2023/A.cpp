#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    std::vector<int> a(n);
    std::vector<std::pair<int, int>> op;
    auto derive = [&](auto& self, int l, int r, const std::vector<int>& idx) {
        if (idx.empty()) {
            return;
        }
        if (l == r - 1) {
            return;
        }
        int m = (l + r) / 2;
        std::vector<int> nxtl, nxtr;
        for (auto i : idx) {
            if (b[i] >= m) {
                nxtr.push_back(i);
            } else {
                nxtl.push_back(i);
            }
        }

        for (auto i : nxtr) {
            a[i] = m;
            op.emplace_back(2, i + 1);
        }
        for (int i = l + 1; i < m; ++i) {
            op.emplace_back(1, i);
        }

        self(self, l, m, nxtl);
        self(self, m, r, nxtr);
    };

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    derive(derive, 0, n + 1, p);

    assert(a == b);

    std::cout << op.size() << "\n";
    for (auto [type, xv] : op) {
        std::cout << type << " " << xv << "\n";
    }

    return 0;
}