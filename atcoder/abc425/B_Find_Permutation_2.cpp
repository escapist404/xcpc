#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 1);

    do {
        bool is = true;
        for (int i = 0; i < n; ++i) {
            if (a[i] != -1) {
                if (p[i] != a[i]) {
                    is = false;
                }
            }
        }

        if (is) {
            std::cout << "Yes\n";
            for (int i = 0; i < n; ++i) {
                std::cout << p[i] << " \n"[i == n - 1];
            }
            return 0;
        }
    } while (std::next_permutation(p.begin(), p.end()));

    std::cout << "No\n";
}