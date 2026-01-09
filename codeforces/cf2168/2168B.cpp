#include <bits/stdc++.h>

void first() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int argmax = std::max_element(a.begin(), a.end()) - a.begin();
    int argmin = std::min_element(a.begin(), a.end()) - a.begin();

    std::cout << (argmax < argmin) << "\n";
}

void second() {
    int n;
    bool x;
    std::cin >> n >> x;

    auto ask = [](const int l, const int r) {
        std::cout << "? " << l + 1 << " " << r << std::endl;
        int ret;
        std::cin >> ret;
        return ret;
    };

    auto report = [](const int x) {
        std::cout << "! " << x + 1 << std::endl;
    };

    if (x) {
        int l = 0, r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (ask(m, n) == n - 1) {
                l = m;
            } else {
                r = m;
            }
        }
        report(l);
    } else {
        int l = 0, r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (ask(0, m) != n - 1) {
                l = m;
            } else {
                r = m;
            }
        }
        report(r - 1);
    }
}

int main() {
    std::string flag;
    std::cin >> flag;

    int tt;
    std::cin >> tt;

    if (flag == "first") {
        while (tt--) {
            first();
        }
    } else {
        while (tt--) {
            second();
        }
    }

    return 0;
}
