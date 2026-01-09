#include <bits/stdc++.h>

namespace interactor {
    std::vector<int> ask(const std::vector<int>& k) {
        std::cout << "? " << k.size();
        std::for_each(k.begin(), k.end(), [](int v) {
            std::cout << " " << v + 1;
        });
        std::cout << std::endl;

        int c;
        std::cin >> c;
        std::vector<int> r(c);
        for (auto& i : r) {
            std::cin >> i;
            --i;
        }

        return r;
    }

    void report(const std::vector<int>& s) {
        std::cout << "!";
        std::for_each(s.begin(), s.end(), [](int v) {
            std::cout << " " << v + 1;
        });
        std::cout << std::endl;
    }
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> vis(n * n + 1, n);
    for (int i = 0; i < n; ++i) {
        std::vector<int> cand;
        for (int j = 0; j < n * n + 1; ++j) {
            if (vis[j] == n) {
                cand.push_back(j);
            }
        }
        auto ret = interactor::ask(cand);
        if (ret.size() > n) {
            ret.resize(n + 1);
            interactor::report(ret);
            return;
        }

        for (const auto& j : ret) {
            vis[j] = i;
        }
    }
    
    std::vector<int> ans;
    for (int i = n * n, c = n + 1; i >= 0 && c >= 0; --i) {
        if (vis[i] == c - 1) {
            c--;
            ans.push_back(i);
        }
    }

    std::reverse(ans.begin(), ans.end());
    interactor::report(ans);
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}