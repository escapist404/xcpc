#include <bits/stdc++.h>

void first() {
    int x;
    std::cin >> x;
    --x;

    int y = x, r = 0;
    for (int i = 0; i < 15; ++i) {
        if (x >> i & 1) {
            r ^= i + 1;
        }
    }
    y ^= r << 15;
    int s = (r ^ (r >> 1) ^ (r >> 2) ^ (r >> 3)) & 1;
    y ^= s << 19;

    std::cout << __builtin_popcount(y) << "\n";
    for (int i = 0; i < 20; ++i) {
        if (y >> i & 1) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n";
}

void second() {
    int n;
    std::cin >> n;

    int y = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        --t;
        y ^= 1 << t;
    }

    int r = y >> 15 & 15;
    int s = y >> 19 & 1;
    int x = y & 32767;

    if (((r ^ (r >> 1) ^ (r >> 2) ^ (r >> 3)) & 1) == s) {
        for (int i = 0; i < 15; ++i) {
            if (x >> i & 1) {
                r ^= i + 1;
            }
        }
        if (r != 0) {
            x ^= 1 << (r - 1);
        }
    }

    std::cout << x + 1 << "\n";
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
