#include <bits/stdc++.h>

namespace interactor {
    int ask(const std::vector<int>& j) {
        std::cout << "? " << j.size();
        for (auto i : j) {
            std::cout << " " << i + 1;
        }
        std::cout << std::endl;
        
        int ret;
        std::cin >> ret;
        return ret;
    }

    void report(const std::vector<int>& a) {
        std::cout << "!";
        for (auto i : a) {
            std::cout << " " << i;
        }
        std::cout << std::endl;
    }
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> p, q, a(2 * n, -1);
    for (int i = 0; i < 2 * n; ++i) {
        p.push_back(i);
        int r = interactor::ask(p);
        if (r != 0) {
            a[i] = r;
            p.pop_back();
            q.push_back(i);
        }
    }

    for (int i = 0; i < 2 * n; ++i) {
        if (a[i] == -1) {
            q.push_back(i);
            int r = interactor::ask(q);
            a[i] = r;
            q.pop_back();
        }
    }

    interactor::report(a);
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}