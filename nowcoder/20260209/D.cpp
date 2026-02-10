#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;
using i128 = __int128;

i128 exgcd(i128 a, i128 b, i128& x, i128& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i128 d = exgcd(b, a % b, x, y);
    i128 x0 = y;
    i128 y0 = x - (a / b) * y;
    x = x0, y = y0;
    return d;
}

std::istream& operator>>(std::istream& is, i128& v) {
    i64 x;
    is >> x;
    v = x;
    return is;
}

std::ostream& operator<<(std::ostream& os, const i128 v) {
    os << (i64)v;
    return os;
}

void solve() {
    i128 c, a, b;
    std::cin >> c >> a >> b;

    i128 x0, y0;
    i128 d = exgcd(a, b, x0, y0);

    if (c % d != 0) {
        std::cout << "No\n";
        return;
    }

    x0 *= c / d;
    y0 *= c / d;
    x0 %= b / d;
    x0 += b / d;
    x0 %= b / d;
    y0 = (c - a * x0) / b;

    if (y0 < 0) {
        std::cout << "No\n";
        return;
    }

    std::cout << "Yes\n";

    i128 k1 = (y0 - x0) / (a / d + b / d) + (((y0 - x0) % (a / d + b / d)) > 0);
    i128 x1 = x0 + k1 * (b / d);
    i128 y1 = y0 - k1 * (a / d);

    i128 k2 = (y0 - x0) / (a / d + b / d);
    i128 x2 = x0 + k2 * (b / d);
    i128 y2 = y0 - k2 * (a / d);

    bool e1 = (a * x1 + b * y1 == c) && x1 >= 0 && y1 >= 0;
    bool e2 = (a * x2 + b * y2 == c) && x2 >= 0 && y2 >= 0;

    if (e1 && e2) {
        if (std::max(x1, y1) < std::max(x2, y2)) {
            std::cout << x1 << " " << y1 << "\n";
        } else {
            std::cout << x2 << " " << y2 << "\n";
        }
    } else if (e1) {
        std::cout << x1 << " " << y1 << "\n";
    } else if (e2) {
        std::cout << x2 << " " << y2 << "\n";
    }

    return;
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
